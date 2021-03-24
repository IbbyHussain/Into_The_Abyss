#include "C_LeverManager.h"
#include "MyProject/GameObjects/SkeletalMeshs/Levers/C_BaseAnimLever.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/GameObjects/StaticMeshs/Buildings/C_SpikeDoor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/ManagerClasses/C_TheLabLevel_ManagerClass.h"
#include "MyProject/C_PlayerCharacter.h"

AC_LeverManager::AC_LeverManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_LeverManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AC_LeverManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_LeverManager::CheckLever()
{
	bool bAllLeversPulled = true;

	// The array that holds the lever actors bCanPullLever bool values.
	//TArray<bool> boolArray;

	// If these are false the levers have been pulled already.
	//Can only be updated here as this variable gets updated when a lever is pressed. Which is where this function is called.
	//boolArray = {!LeverArray[0]->bCanPullLever, !LeverArray[1]->bCanPullLever, !LeverArray[2]->bCanPullLever };

	// Use a bp event so we can have more control on how many elements in the array (how many levers)
	UpdateboolArray();

	// for every value in the array.
	for (bool x : boolArray)
	{
		// if a value in the array is false will break (goes to the top of the loop?)
		if (!x)
		{
			bAllLeversPulled = false;
			break;
		}
	}

	// if all values in the array are true
	if (bAllLeversPulled)
	{
		UE_LOG(LogTemp, Log, TEXT("All levers have been pulled_______Execute next command"));

		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_LeverManager::ChangeCameraView, 1.0f, false);
		GetWorldTimerManager().SetTimer(ResetCameraViewHandle, this, &AC_LeverManager::ResetCameraView, 4.0f, false);
		PlayerCharacter->MovementState = EMovementState::NONE;
		PlayerCharacter->UpdateMovement();
		PlayerCharacter->bLockCamera = true;

		bIsComplete = true;
	}
}

void AC_LeverManager::ChangeCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(CameraViewPoint, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_LeverManager::PlaySpikeDoorAnimation, 1.0f, false);
	}
}

void AC_LeverManager::ResetCameraView()
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		GetWorldTimerManager().SetTimer(CameraViewHandle, this, &AC_LeverManager::ResetMovement, 1.0f, false);
	}
}

void AC_LeverManager::ResetMovement()
{
	PlayerCharacter->MovementState = EMovementState::STANDING;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = false;
	GetWorldTimerManager().ClearTimer(CameraViewHandle);
}

void AC_LeverManager::PlaySpikeDoorAnimation()
{
	for (auto x : DoorArray)
	{
		x->PlayOpenDoorAnimation();
		GetWorldTimerManager().ClearTimer(CameraViewHandle);
	}
}

	

