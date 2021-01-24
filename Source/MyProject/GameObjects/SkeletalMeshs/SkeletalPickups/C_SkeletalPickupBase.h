// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/SkeletalMeshs/C_SkeletalMeshActorPhysics.h"
#include "C_SkeletalPickupBase.generated.h"

UCLASS()
class MYPROJECT_API AC_SkeletalPickupBase : public AC_SkeletalMeshActorPhysics
{
	GENERATED_BODY()

public:
	AC_SkeletalPickupBase();

protected:

	// The sound that will be played when the player overlaps with this pickup
	UPROPERTY(EditDefaultsOnly, Category = "CPP")
	USoundBase* PickupSound;

	// Function called when base classes are interacted with.
	void OnInteract(float& Stat, float Amount);

	// A basic version of OnInteract, No image is displayed and does not perform an operation on a variable.
	void OnInteractBasic();

	void DisplayInteractImage();

	UPROPERTY(EditDefaultsOnly, Category = "CPP")
	class UBoxComponent* BoxComp;

	FTimerHandle DespawnHandle;

	void DestroyThis();

	bool bDespawn;

	// Player HUD pointer
	class AC_PlayerHUD2* PlayerHUD;

	class AC_PlayerCharacter* PlayerCharacter;

	virtual void BeginPlay() override;
};
