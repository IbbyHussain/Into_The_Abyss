// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseLever.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/GameObjects/StaticMeshs/Buildings/C_SpikeDoor.h"

AC_BaseLever::AC_BaseLever()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AC_BaseLever::OnOverlapBeginLever);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AC_BaseLever::OnOverlapEndLever);

	bShowEKeyHint = true;

	bCanPullLever = true;

	bOverlappingLever = false;
}

void AC_BaseLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Opens the chest 
	if (OverlappingLeverBoxCollision() && PlayerCharacter->bEKeyPressed && bCanPullLever)
	{
		MeshComp->PlayAnimation(LeverPulledAnimation, false);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LeverPulledSound, GetActorLocation());
		bShowEKeyHint = false;
		bCanPullLever = false;
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_BaseLever::ChangeCameraView, 1.0f, false);
		GetWorldTimerManager().SetTimer(ResetCameraViewHandle, this, &AC_BaseLever::ResetCameraView, 4.0f, false);
		PlayerCharacter->MovementState = EMovementState::NONE;
		PlayerCharacter->UpdateMovement();
		PlayerCharacter->bLockCamera = true;
	}
}

void AC_BaseLever::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AC_BaseLever::OnOverlapBeginLever(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor == PlayerCharacter)
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
}

void AC_BaseLever::OnOverlapEndLever(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == PlayerCharacter && (OtherActor != this))
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
}

bool AC_BaseLever::OverlappingLeverBoxCollision()
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

void AC_BaseLever::ChangeCameraView()
{
	if(PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(CameraViewPoint, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_BaseLever::PlaySpikeDoorAnimation, 1.0f, false);
	}
}

void AC_BaseLever::ResetCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_BaseLever::ResetMovement, 1.0f, false);
	}
}

void AC_BaseLever::ResetMovement()
{
	PlayerCharacter->MovementState = EMovementState::STANDING;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = false;
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}

void AC_BaseLever::PlaySpikeDoorAnimation()
{
	SpikeDoor->PlayOpenDoorAnimation();
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}