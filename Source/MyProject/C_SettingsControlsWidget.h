// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/InputSettings.h"
#include "Components/InputKeySelector.h"
#include "GameFramework/PlayerInput.h"
#include "C_SettingsControlsWidget.generated.h"



UCLASS()
class MYPROJECT_API UC_SettingsControlsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UFUNCTION()
	void BackButtonClicked();

	class AC_PlayerHUD2* HUD;

	class UInputSettings* Input;

	void RemapActionBinding(FInputChord InputChord, FName ActionName, UInputKeySelector* KeySelectorButton);

	void RemapAxisBinding(FInputChord InputChord, FName AxisName, float AxisValue, UInputKeySelector* KeySelectorButton);

	// INTERACT

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* InteractButton;

	UFUNCTION()
	void InteractButtonClicked(FInputChord InputChord);

	// WEAPON WHEEL

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* WeaponWheelButton;

	UFUNCTION()
	void WeaponWheelButtonClicked(FInputChord InputChord);

	// SETTINGS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* SettingsButton;

	UFUNCTION()
	void SettingsButtonClicked(FInputChord InputChord);

	// JUMP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* JumpButton;
	
	UFUNCTION()
	void JumpButtonClicked(FInputChord InputChord);

	// DASH

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* DashButton;

	UFUNCTION()
	void DashButtonClicked(FInputChord InputChord);

	// CROUCH

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* CrouchButton;

	UFUNCTION()
	void CrouchButtonClicked(FInputChord InputChord);

	// SPRINT

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* SprintButton;

	UFUNCTION()
	void SprintButtonClicked(FInputChord InputChord);

	// ABILITY 1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* Ability1Button;

	UFUNCTION()
	void Ability1ButtonClicked(FInputChord InputChord);

	// ABILITY 2

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* Ability2Button;

	UFUNCTION()
	void Ability2ButtonClicked(FInputChord InputChord);

	// ABILITY 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* Ability3Button;

	UFUNCTION()
	void Ability3ButtonClicked(FInputChord InputChord);

	// ABILITY 4

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* Ability4Button;

	UFUNCTION()
	void Ability4ButtonClicked(FInputChord InputChord);

	// AIM

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* AimButton;

	UFUNCTION()
	void AimButtonClicked(FInputChord InputChord);

	// FIRE

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* FireButton;

	UFUNCTION()
	void FireButtonClicked(FInputChord InputChord);

	// BLOCK

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* BlockButton;

	UFUNCTION()
	void BlockButtonClicked(FInputChord InputChord);

	// SHIELD BASH

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* BashButton;

	UFUNCTION()
	void BashButtonClicked(FInputChord InputChord);

	// BASIC ATTACK

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* AttackButton;

	UFUNCTION()
	void AttackButtonClicked(FInputChord InputChord);

	// DOWNWARD ATTACK

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* Attack2Button;

	UFUNCTION()
	void Attack2ButtonClicked(FInputChord InputChord);

	// MOVE FORWARD

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* MFButton;

	UFUNCTION()
	void MFButtonClicked(FInputChord InputChord);

	// MOVE BACKWARD

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* MBButton;

	UFUNCTION()
	void MBButtonClicked(FInputChord InputChord);

	// MOVE RIGHT

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* MRButton;

	UFUNCTION()
	void MRButtonClicked(FInputChord InputChord);

	// MOVE LEFT

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* MLButton;

	UFUNCTION()
	void MLButtonClicked(FInputChord InputChord);

	// Saving 

	void SaveKeyText();

	void LoadKeyText();

	TArray<UInputKeySelector*> KeySelectorArray;

};