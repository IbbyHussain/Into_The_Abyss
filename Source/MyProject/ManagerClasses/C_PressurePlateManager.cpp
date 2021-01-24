// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PressurePlateManager.h"
#include "MyProject/GameObjects/StaticMeshs/Buildings/C_SpikeDoor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/GameObjects/StaticMeshs/Interactables/Puzzles/C_PressurePlate.h"
#include "MyProject/ManagerClasses/C_TheLabLevel_ManagerClass.h"

// Sets default values
AC_PressurePlateManager::AC_PressurePlateManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bDoOnce = true;
}

// Called every frame
void AC_PressurePlateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(b1PressurePlate)
	{
		if (PressurePlate1->bIsActivated && bDoOnce)
		{
			PuzzleComplete();
		}
	}

	else if (b2PressurePlates)
	{
		if (PressurePlate1->bIsActivated && PressurePlate2->bIsActivated && bDoOnce)
		{
			PuzzleComplete();
		}
	}

	else if (b3PressurePlates)
	{
		if (PressurePlate1->bIsActivated && PressurePlate2->bIsActivated && PressurePlate3->bIsActivated && bDoOnce)
		{
			PuzzleComplete();
		}
	}
}

void AC_PressurePlateManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterRef = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AC_PressurePlateManager::PuzzleComplete()
{
	bDoOnce = false;
	GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_PressurePlateManager::ChangeCameraView, 1.0f, false);
	GetWorldTimerManager().SetTimer(ResetCameraViewHandle, this, &AC_PressurePlateManager::ResetCameraView, 4.0f, false);
	PlayerCharacterRef->MovementState = EMovementState::NONE;
	PlayerCharacterRef->UpdateMovement();
	PlayerCharacterRef->bLockCamera = true;

	bIsComplete = true;

	if (LevelManager)
	{
		LevelManager->Update();
	}
}


void AC_PressurePlateManager::ChangeCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(CameraViewActor, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_PressurePlateManager::PlaySpikeDoorAnimation, 1.0f, false);
	}
}

void AC_PressurePlateManager::ResetCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(PlayerCharacterRef, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_PressurePlateManager::ResetPlayerMovement, 1.0f, false);
	}
}

void AC_PressurePlateManager::ResetPlayerMovement()
{
	PlayerCharacterRef->MovementState = EMovementState::STANDING;
	PlayerCharacterRef->UpdateMovement();
	PlayerCharacterRef->bLockCamera = false;
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}

void AC_PressurePlateManager::PlaySpikeDoorAnimation()
{
	for (auto x : DoorArray)
	{
		x->PlayOpenDoorAnimation();
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
	}
}
