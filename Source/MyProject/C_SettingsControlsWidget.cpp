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

	// Misc Action Remappings
	InteractButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::InteractButtonClicked);
	WeaponWheelButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::WeaponWheelButtonClicked);
	SettingsButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::SettingsButtonClicked);

	// Movement Action Remappings
	JumpButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::JumpButtonClicked);
	DashButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::DashButtonClicked);
	CrouchButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::CrouchButtonClicked);
	SlideButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::SlideButtonClicked);
	SprintButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::SprintButtonClicked);

	// Magic Action Remappings
	Ability1Button->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::Ability1ButtonClicked);
	Ability2Button->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::Ability2ButtonClicked);
	Ability3Button->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::Ability3ButtonClicked);
	Ability4Button->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::Ability4ButtonClicked);

	//// Sword and Shield Action Remappings
	BlockButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::BlockButtonClicked);
	BashButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::BashButtonClicked);
	AttackButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::AttackButtonClicked);
	Attack2Button->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::Attack2ButtonClicked);

	// Crossbow Action Remappings
	AimButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::AimButtonClicked);
	FireButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::FireButtonClicked);
}

void UC_SettingsControlsWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}

// Will remap any action binding
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

void UC_SettingsControlsWidget::InteractButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Interact"));
}

void UC_SettingsControlsWidget::WeaponWheelButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("WeaponWheel"));
}

void UC_SettingsControlsWidget::SettingsButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Settings"));
}

void UC_SettingsControlsWidget::JumpButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Jump"));
}

void UC_SettingsControlsWidget::DashButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Dash"));
}

void UC_SettingsControlsWidget::CrouchButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Crouch"));
}

void UC_SettingsControlsWidget::SlideButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Slide"));
}

void UC_SettingsControlsWidget::SprintButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Sprint"));
}

void UC_SettingsControlsWidget::Ability1ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability1"));
}

void UC_SettingsControlsWidget::Ability2ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability2"));
}

void UC_SettingsControlsWidget::Ability3ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability3"));
}

void UC_SettingsControlsWidget::Ability4ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability4"));
}

void UC_SettingsControlsWidget::AimButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Aiming"));
}

void UC_SettingsControlsWidget::FireButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Fire"));
}

void UC_SettingsControlsWidget::BlockButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Blocking"));
}

void UC_SettingsControlsWidget::BashButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("ShieldBash"));
}

void UC_SettingsControlsWidget::AttackButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("DefaultAttack"));
}

void UC_SettingsControlsWidget::Attack2ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Thrust"));
}
