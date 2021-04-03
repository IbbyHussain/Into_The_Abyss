// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SavingManager.generated.h"

UCLASS()
class MYPROJECT_API AC_SavingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_SavingManager();

	void CheckForSave();

	// The default location the player will spawn if they have not interacted with a checkpoint.
	UPROPERTY(EditInstanceOnly, Category = "Exposed")
	FVector DefaultPlayerLocation;

	UPROPERTY(EditInstanceOnly, Category = "Exposed")
	FRotator DefaultPlayerRotation;

	// Player locked variables

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Locked Variables")
	bool bIsDashLocked;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Locked Variables")
	bool bIsCrouchLocked;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Locked Variables")
	bool bIsSlideLocked;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Locked Variables")
	bool bIsWeaponWheelLocked;

	// HUD Locked Variables

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Widget Locked Variables")
	bool bDisableMagicBar;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Widget Locked Variables")
	bool bDisableHealthBar;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Widget Locked Variables")
	bool bDisableSouls;

	// Weapon Locked Variables

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Weapon Locked Variables")
	bool bUnlockSword;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Weapon Locked Variables")
	bool bUnlockMagic;

	UPROPERTY(EditInstanceOnly, Category = "Exposed| Weapon Locked Variables")
	bool bUnlockCrossbow;

protected:
	virtual void BeginPlay() override;

	class AC_PlayerCharacter* PlayerCharacter;

};
