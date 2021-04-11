// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsControlsWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "GameFramework/InputSettings.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/InputKeySelector.h"

#include "Misc/C_BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"

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

	// Moving Axis Mappings
	MFButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::MFButtonClicked);
	MBButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::MBButtonClicked);
	MRButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::MRButtonClicked);
	MLButton->OnKeySelected.AddDynamic(this, &UC_SettingsControlsWidget::MLButtonClicked);

	KeySelectorArray = { InteractButton, WeaponWheelButton, SettingsButton, JumpButton, DashButton, CrouchButton, SprintButton, Ability1Button, Ability2Button, Ability3Button, Ability4Button,
	BlockButton, BashButton, Attack2Button, AttackButton, AimButton, FireButton, MFButton, MBButton, MRButton, MLButton};

	// Loads player's changes
	LoadKeyText();
}

void UC_SettingsControlsWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();

		// Saves player's changes
		SaveKeyText();
		RemoveFromParent();
	}
}

// Will remap any action binding
void UC_SettingsControlsWidget::RemapActionBinding(FInputChord InputChord, FName ActionName, UInputKeySelector* KeySelectorButton)
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

	KeySelectorButton->SetNoKeySpecifiedText(NewMapping.Key.GetDisplayName());

	// Saves the mapping 
	Input->SaveKeyMappings();
	Input->SaveConfig();
}

// Will remap any axis binding
void UC_SettingsControlsWidget::RemapAxisBinding(FInputChord InputChord, FName AxisName, float AxisValue, UInputKeySelector* KeySelectorButton)
{
	TArray <FInputAxisKeyMapping> OutMappings;
	Input->GetAxisMappingByName(AxisName, OutMappings);

	for (auto i : OutMappings)
	{
		// If the mapping is a certain scale
		if (i.Scale == AxisValue)
		{
			FInputAxisKeyMapping NewMapping;
			NewMapping.AxisName = i.AxisName;
			NewMapping.Key = i.Key;
			NewMapping.Scale = AxisValue;

			// Remove that mapping - This does not remove all mappings just the mapping with that specific scale
			Input->RemoveAxisMapping(NewMapping, false);
		} 
	}

	// Set the new mapping
	FInputAxisKeyMapping FinalMapping;
	FinalMapping.AxisName = AxisName;
	FinalMapping.Scale = AxisValue;
	FinalMapping.Key = InputChord.Key;

	Input->AddAxisMapping(FinalMapping, true);

	KeySelectorButton->SetNoKeySpecifiedText(FinalMapping.Key.GetDisplayName());

	// Saves the mapping 
	Input->SaveKeyMappings();
	Input->SaveConfig();
}

// ACTION MAPPINGS

void UC_SettingsControlsWidget::InteractButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Interact"), InteractButton);
}

void UC_SettingsControlsWidget::WeaponWheelButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("WeaponWheel"), WeaponWheelButton);
}

void UC_SettingsControlsWidget::SettingsButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Settings"), SettingsButton);
}

void UC_SettingsControlsWidget::JumpButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Jump"), JumpButton);
}

void UC_SettingsControlsWidget::DashButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Dash"), DashButton);
}

void UC_SettingsControlsWidget::CrouchButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Crouch"), CrouchButton);
}

void UC_SettingsControlsWidget::SprintButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Sprint"), SprintButton);
}

void UC_SettingsControlsWidget::Ability1ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability1"), Ability1Button);
}

void UC_SettingsControlsWidget::Ability2ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability2"), Ability2Button);
}

void UC_SettingsControlsWidget::Ability3ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability3"), Ability3Button);
}

void UC_SettingsControlsWidget::Ability4ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability4"),Ability4Button);
}

void UC_SettingsControlsWidget::AimButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Aiming"), AimButton);
}

void UC_SettingsControlsWidget::FireButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Fire"), FireButton);
}

void UC_SettingsControlsWidget::BlockButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Blocking"), BlockButton);
}

void UC_SettingsControlsWidget::BashButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("ShieldBash"), BashButton);
}

void UC_SettingsControlsWidget::AttackButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("DefaultAttack"), AttackButton);
}

void UC_SettingsControlsWidget::Attack2ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Thrust"), Attack2Button);
}

// AXIS MAPPINGS

void UC_SettingsControlsWidget::MFButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveForward"), 1.0f, MFButton);
}

void UC_SettingsControlsWidget::MBButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveForward"), -1.0f, MBButton);
}

void UC_SettingsControlsWidget::MRButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveRight"), 1.0f, MRButton);
}

void UC_SettingsControlsWidget::MLButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveRight"), -1.0f, MLButton);
}

// Saving

void UC_SettingsControlsWidget::SaveKeyText()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		for (int i = 0; i < KeySelectorArray.Num(); i++)
		{
			// Save the names of the new inputs
			FString a = KeySelectorArray[i]->NoKeySpecifiedText.ToString();
			SaveGameInstance->KeyNameArray[i] = a;
		}

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Keys"), 0))
		{
			//UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Saved KEY name"));
		}
	}
}

void UC_SettingsControlsWidget::LoadKeyText()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Keys"), 0)))
	{
		for(int i = 0; i < KeySelectorArray.Num(); i++)
		{
			// Loads the names of the new inputs
			KeySelectorArray[i]->SetNoKeySpecifiedText(FText::FromString(LoadedGame->KeyNameArray[i]));
		}
	}
}