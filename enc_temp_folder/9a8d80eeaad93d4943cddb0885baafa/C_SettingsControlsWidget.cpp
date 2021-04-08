// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsControlsWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "GameFramework/InputSettings.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/InputKeySelector.h"

void UC_SettingsControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Input = UInputSettings::GetInputSettings();

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsControlsWidget::BackButtonClicked);

	// Remappings
	JumpButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::JumpButtonClicked);
}

void UC_SettingsControlsWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}

void UC_SettingsControlsWidget::RemapActionBinding(FInputChord InputChord, FName ActionName)
{
	TArray <FInputActionKeyMapping> OutMappings;

	Input->GetActionMappingByName(ActionName, OutMappings);

	// Remove all keys associated with the mapping
	for (auto i : OutMappings)
	{
		Input->RemoveActionMapping(i, false);
	}

	// Create a new mapping
	FInputActionKeyMapping NewMapping;

	// New mapping will use the same settings as old mapping
	NewMapping.bShift = InputChord.bShift;
	NewMapping.bCtrl = InputChord.bCtrl;
	NewMapping.bAlt = InputChord.bAlt;
	NewMapping.bCmd = InputChord.bCmd;
	NewMapping.Key = InputChord.Key;

	NewMapping.ActionName = ActionName;

	// Adds new mapping
	Input->AddActionMapping(NewMapping, true);

	// Saves the mapping 
	Input->SaveKeyMappings();
	Input->SaveConfig();
}

void UC_SettingsControlsWidget::JumpButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Jump"));
}
