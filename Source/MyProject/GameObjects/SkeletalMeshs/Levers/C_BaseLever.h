// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_SkeletalMeshActor.h"
#include "C_BaseLever.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AC_BaseLever : public AC_SkeletalMeshActor
{
	GENERATED_BODY()
protected:
	AC_BaseLever();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Lever")
	UBoxComponent* BoxComp;

	//Pulled Sound
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	USoundBase* LeverPulledSound;

	//The spike door that will be opened
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	class AC_SpikeDoor* SpikeDoor;

	//The animation to be played when the lever is pulled
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	class UAnimationAsset* LeverPulledAnimation;

	//The actor that will give the viewpoint of the camera 
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	AActor* CameraViewPoint;

	// pointer to this, so that correct lever will play animation and open
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	AC_BaseLever* Self;

	bool bShowEKeyHint;

	bool bCanPullLever;

	bool bOverlappingLever;

	bool OverlappingLeverBoxCollision();

	void ChangeCameraView();

	void ResetCameraView();

	FTimerHandle ResetCameraViewHandle;

	FTimerHandle CameraViewHandle;

	void ResetMovement();

	void PlaySpikeDoorAnimation();

	UFUNCTION()
	void OnOverlapBeginLever(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndLever(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	class AC_PlayerCharacter* PlayerCharacter;

	class APlayerController* PlayerController;

	class AC_PlayerHUD2* HUD;

	USceneComponent* SceneComp;
};
