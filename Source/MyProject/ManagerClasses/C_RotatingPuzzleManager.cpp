// Fill out your copyright notice in the Description page of Project Settings.


#include "C_RotatingPuzzleManager.h"
#include "MyProject/GameObjects/StaticMeshs/Interactables/Puzzles/C_RotatingPuzzleActor.h"
#include "MyProject/GameObjects/StaticMeshs/Buildings/C_SpikeDoor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/ManagerClasses/C_TheLabLevel_ManagerClass.h"
#include "MyProject/Quest System/C_BaseQuest.h"

AC_RotatingPuzzleManager::AC_RotatingPuzzleManager()
{
	PrimaryActorTick.bCanEverTick = true;

	bDoOnce = true;
}

void AC_RotatingPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(b1RotatingPuzzle)
	{
		if (RotatingPuzzle1->bRightDirection && bDoOnce)
		{
			PuzzleComplete();
		}
	}

	if (b2RotatingPuzzles)
	{
		if (RotatingPuzzle1->bRightDirection && RotatingPuzzle2->bRightDirection && bDoOnce)
		{
			PuzzleComplete();
		}
	}

	if (b3RotatingPuzzles)
	{
		if (RotatingPuzzle1->bRightDirection && RotatingPuzzle2->bRightDirection && RotatingPuzzle3->bRightDirection && bDoOnce)
		{
			PuzzleComplete();
		}
	}
}

void AC_RotatingPuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AC_RotatingPuzzleManager::PuzzleComplete()
{
	bDoOnce = false;
	GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_RotatingPuzzleManager::ChangeCameraView, 1.0f, false);
	GetWorldTimerManager().SetTimer(ResetCameraViewHandle, this, &AC_RotatingPuzzleManager::ResetCameraView, 4.0f, false);
	PlayerCharacter->MovementState = EMovementState::NONE;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = true;
	HUD->MakeEKeyHintInVisible();

	bIsComplete = true;

	if (LevelManager)
	{
		LevelManager->Update();
	}

	// Objective complete here
	if(Quest)
	{
		Quest->CheckPuzzleObjectiveDelegate.Broadcast(RotatingPuzzle1);
	}
}

void AC_RotatingPuzzleManager::ChangeCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(CameraViewActor, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_RotatingPuzzleManager::PlaySpikeDoorAnimation, 1.0f, false);
	}
}

void AC_RotatingPuzzleManager::ResetCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_RotatingPuzzleManager::ResetPlayerMovement, 1.0f, false);
	}
}

void AC_RotatingPuzzleManager::ResetPlayerMovement()
{
	PlayerCharacter->MovementState = EMovementState::STANDING;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = false;
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
	HUD->MakeEKeyHintVisible();
}

void AC_RotatingPuzzleManager::PlaySpikeDoorAnimation()
{
	SpikeDoor->PlayOpenDoorAnimation();
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}



