// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_SkeletalMeshAnimActor.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "C_ChestActorBase.generated.h"

class AC_Pickup;
class AC_PlayerCharacter;

UCLASS()
class MYPROJECT_API AC_ChestActorBase : public AC_SkeletalMeshAnimActor, public IC_InteractInterface
{
	GENERATED_BODY()

public:

	void PastPlaneVisibility();

	void FuturePlaneVisibility();
protected:
	AC_ChestActorBase();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	USceneComponent* Root;

	// Chest lid collision for dynamic collision
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	UStaticMeshComponent* ChestLid;

	//This is the plane that acts as the glow effect
	UPROPERTY(EditDefaultsOnly = "Glow Effect")
	UStaticMeshComponent* PastPlane;

	//This is the plane that acts as the glow effect
	UPROPERTY(EditDefaultsOnly = "Glow Effect")
	UStaticMeshComponent* FuturePlane;

	// The animation to be played when the chest opens
	UPROPERTY(EditInstanceOnly, Category = "Chest")
	class UAnimationAsset* ChestOpenAnimation;

	UPROPERTY(EditInstanceOnly, Category = "Chest")
	class UAnimationAsset* ChestOpenFutureAnimation;

	// The curve that controlls how the material will fade out
	UPROPERTY(EditDefaultsOnly, Category = "Material Fade")
	UCurveFloat* FMaterialFadeCurve;

	//The location where the pick up will initially spawn
	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	USceneComponent* PickupSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Glow Effect")
	class UPostProcessComponent* PostProcessVolume;

	//The sund to be played when the chest is opened
	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	USoundBase* ChestOpenSound;

	//Which pick up will be spawned for this instance
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Chest")
	TSubclassOf<AActor> PickupClass;

	// The material of the chest effect
	UPROPERTY(EditDefaultsOnly, Category = "Material Fade")
	UMaterialInterface* ChestMaterialGlow;

	// pointer to this, so that correct chest will play animation and open
	UPROPERTY(EditInstanceOnly, Category = "Chest")
	AC_ChestActorBase* Self;

	//Spawns the pick up class
	UFUNCTION(BlueprintCallable)
	void SpawnPickup(FVector Location, FRotator Rotation);

	UFUNCTION()
	void MaterialFadeTimelineFloatReturn(float Alpha);

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

private:

	//Reference to the player character
	AC_PlayerCharacter* PlayerCharacter;

	//Reference to the HUD
	class AC_PlayerHUD2* HUD;

	//Reference to the pick up
	class AC_SkeletalPickupBase* Pickup;

	UMaterialInstanceDynamic* DynamicChestMaterialGlow;

	UTimelineComponent* MaterialFadeTimeline;

	FOnTimelineFloat MaterialFadeInterpFunction{};

	bool bCanOpenChest;

	bool bShowEKeyHint;

	bool bOverlapping;

	bool OverlappingBoxCollision();

	FTimerHandle OpenChestSoundHandle;

	void PlayOpenChestSound();

	// The socket name  of where to attach the chest lid collision so that it moves whilst the animation is playing
	FName ChestLidSocketName;

	//Launch Pickup
	void LaunchPickup();

	void StartLaunch();

	FTimerHandle LaunchHandle;
	
};
