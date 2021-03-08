// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseAnimLever.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/GameObjects/StaticMeshs/Buildings/C_SpikeDoor.h"
#include "MyProject/ManagerClasses/C_LeverManager.h"
#include "MyProject/Quest System/C_BaseQuest.h"

AC_BaseAnimLever::AC_BaseAnimLever()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	PastMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	FutureMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	bShowEKeyHint = true;

	bCanPullLever = true;

	bOverlappingLever = false;
}

void AC_BaseAnimLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_BaseAnimLever::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

bool AC_BaseAnimLever::OverlappingLeverBoxCollision()
{
	if (BoxComp->IsOverlappingActor(PlayerCharacter))
	{
		bOverlappingLever = true;
		return bOverlappingLever;
	}

	else
	{
		bOverlappingLever = false;
		return bOverlappingLever;
	}
}

void AC_BaseAnimLever::ChangeCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(CameraViewPoint, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_BaseAnimLever::PlaySpikeDoorAnimation, 1.0f, false);
	}
}

void AC_BaseAnimLever::ResetCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_BaseAnimLever::ResetMovement, 1.0f, false);
	}
}

void AC_BaseAnimLever::ResetMovement()
{
	PlayerCharacter->MovementState = EMovementState::STANDING;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = false;
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}

void AC_BaseAnimLever::PlaySpikeDoorAnimation()
{
	SpikeDoor->PlayOpenDoorAnimation();
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}

void AC_BaseAnimLever::Interact_Implementation()
{
	if (OverlappingLeverBoxCollision()  && bCanPullLever)
	{
		RemoveKeyHint_Implementation();
		PastMesh->PlayAnimation(LeverPastPulledAnimation, false);
		FutureMesh->PlayAnimation(LeverFuturePulledAnimation, false);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LeverPulledSound, GetActorLocation());
		bShowEKeyHint = false;
		bCanPullLever = false;

		// If the levers need to do something specific will use the mananger class.
		if (Manager)
		{
			// Does soemthing specific
			Manager->CheckLever();
		}

		else
		{
			GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_BaseAnimLever::ChangeCameraView, 1.0f, false);
			GetWorldTimerManager().SetTimer(ResetCameraViewHandle, this, &AC_BaseAnimLever::ResetCameraView, 4.0f, false);
			PlayerCharacter->MovementState = EMovementState::NONE;
			PlayerCharacter->UpdateMovement();
			PlayerCharacter->bLockCamera = true;
		}

		if(Quest)
		{
			Quest->CheckPuzzleObjectiveDelegate.Broadcast(this);
		}
	}
}

void AC_BaseAnimLever::DisplayKeyHint_Implementation()
{
	if (bShowEKeyHint)
	{
		PlayerCharacter->bCanPullLever = true;

		if (HUD)
		{
			HUD->SetEKeyHintText("Pull");
			HUD->MakeEKeyHintVisible();
		}
	}
}

void AC_BaseAnimLever::RemoveKeyHint_Implementation()
{
	if (bShowEKeyHint)
	{
		if (HUD)
		{
			HUD->MakeEKeyHintInVisible();
		}

		PlayerCharacter->bCanPullLever = false;
	}
}