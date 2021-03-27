// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_SkeletalMeshAnimActor.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_BaseAnimLever.generated.h"

class UBoxComponent;
class AC_LeverManager;

UCLASS()
class MYPROJECT_API AC_BaseAnimLever : public AC_SkeletalMeshAnimActor, public IC_InteractInterface
{
	GENERATED_BODY()

public:
	AC_BaseAnimLever();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category = "Lever")
	AC_LeverManager* Manager;

	UPROPERTY(EditDefaultsOnly, Category = "Lever")
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Lever")
	UBoxComponent* Collision;

	//Pulled Sound
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	USoundBase* LeverPulledSound;

	//The spike door that will be opened
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	class AC_SpikeDoor* SpikeDoor;

	//The animation to be played when the lever is pulled
	UPROPERTY(EditDefaultsOnly, Category = "Lever")
	class UAnimationAsset* LeverPastPulledAnimation;

	//The animation to be played when the lever is pulled
	UPROPERTY(EditDefaultsOnly, Category = "Lever")
	class UAnimationAsset* LeverFuturePulledAnimation;

	//The actor that will give the viewpoint of the camera 
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	AActor* CameraViewPoint;

	// pointer to this, so that correct lever will play animation and open
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	AC_BaseAnimLever* Self;

	bool bShowEKeyHint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Lever")
	bool bCanPullLever;

	bool bOverlappingLever;

	bool OverlappingLeverBoxCollision();

	void ChangeCameraView();

	void ResetCameraView();

	FTimerHandle ResetCameraViewHandle;

	FTimerHandle CameraViewHandle;

	void ResetMovement();

	void PlaySpikeDoorAnimation();

	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;

	// DisplayKeyhint function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisplayKeyHint();

	// Implementation of the DisplayKeyHint function
	virtual void DisplayKeyHint_Implementation() override;

	// RemoveKeyhint function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveKeyHint();

	// Implementation of the RemoveKeyHint function
	virtual void RemoveKeyHint_Implementation() override;

	// The quest that needs this puzzle to complete an objective
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lever")
	class AC_BaseQuest* Quest;

private:
	class AC_PlayerCharacter* PlayerCharacter;

	class APlayerController* PlayerController;

	class AC_PlayerHUD2* HUD;

	UPROPERTY()
	USceneComponent* SceneComp;
	
};
