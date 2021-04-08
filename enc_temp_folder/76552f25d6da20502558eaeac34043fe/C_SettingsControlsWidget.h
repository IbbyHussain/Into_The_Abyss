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

	// Misc Remappings

	// Interact

	// Weapon wheel

	// Settings

	// Combat Remappings

	// Sword and Shield

	// Block

	// Default Attack

	// Shield Bash

	// Downward Attack

	// Magic

	// Ability1
	// Ability2
	// Ability3
	// Ability4

	// Crossbow Mappings

	// Aim

	// Fire

	void RemapActionBinding(FInputChord InputChord, FName ActionName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UInputKeySelector* JumpButton;
	
	UFUNCTION()
	void JumpButtonClicked(FInputChord InputChord);
};