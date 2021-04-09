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

	LoadKeyText();
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
void UC_SettingsControlsWidget::RemapActionBinding(FInputChord InputChord, FName ActionName, UInputKeySelector* KeySelectorButton, int32 Index)
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

	//KeySelectorButton->SetNoKeySpecifiedText(NewMapping.Key.GetDisplayName());

	// Saves the mapping 
	Input->SaveKeyMappings();
	Input->SaveConfig();

	SaveKeyText(Index, NewMapping.Key.GetDisplayName().ToString());
}

// Will remap any axis binding
void UC_SettingsControlsWidget::RemapAxisBinding(FInputChord InputChord, FName AxisName, float AxisValue)
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

	// Saves the mapping 
	Input->SaveKeyMappings();
	Input->SaveConfig();
}

// ACTION MAPPINGS

void UC_SettingsControlsWidget::InteractButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Interact"), InteractButton, 0);
}

void UC_SettingsControlsWidget::WeaponWheelButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("WeaponWheel"), WeaponWheelButton, 1);
}

void UC_SettingsControlsWidget::SettingsButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Settings"), SettingsButton, 2);
}

void UC_SettingsControlsWidget::JumpButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Jump"), JumpButton, 3);
}

void UC_SettingsControlsWidget::DashButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Dash"), DashButton, 4);
}

void UC_SettingsControlsWidget::CrouchButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Crouch"), CrouchButton, 5);
}

void UC_SettingsControlsWidget::SprintButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Sprint"), SprintButton, 6);
}

void UC_SettingsControlsWidget::Ability1ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability1"), Ability1Button, 7);
}

void UC_SettingsControlsWidget::Ability2ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability2"), Ability2Button, 8);
}

void UC_SettingsControlsWidget::Ability3ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability3"), Ability3Button, 9);
}

void UC_SettingsControlsWidget::Ability4ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Ability4"),Ability4Button, 10);
}

void UC_SettingsControlsWidget::AimButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Aiming"), AimButton, 11);
}

void UC_SettingsControlsWidget::FireButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Fire"), FireButton, 12);
}

void UC_SettingsControlsWidget::BlockButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Blocking"), BlockButton, 13);
}

void UC_SettingsControlsWidget::BashButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("ShieldBash"), BashButton, 14);
}

void UC_SettingsControlsWidget::AttackButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("DefaultAttack"), AttackButton, 15);
}

void UC_SettingsControlsWidget::Attack2ButtonClicked(FInputChord InputChord)
{
	RemapActionBinding(InputChord, FName("Thrust"), Attack2Button, 16);
}

// AXIS MAPPINGS

void UC_SettingsControlsWidget::MFButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveForward"), 1.0f);
}

void UC_SettingsControlsWidget::MBButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveForward"), -1.0f);
}

void UC_SettingsControlsWidget::MRButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveRight"), 1.0f);
}

void UC_SettingsControlsWidget::MLButtonClicked(FInputChord InputChord)
{
	RemapAxisBinding(InputChord, FName("MoveRight"), -1.0f);
}

void UC_SettingsControlsWidget::SaveKeyText(int32 Index, FString KeyName)
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->KeyNameArray[0] = KeyName;
		UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key name is: %s"), *SaveGameInstance->KeyNameArray[0]);

		//SaveGameInstance->SavedKey = KeyName; 
		//UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key name is: %s"), *SaveGameInstance->SavedKey);

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
		KeySelectorArray[0]->SetNoKeySpecifiedText(FText::FromString(LoadedGame->KeyNameArray[0]));
		UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key SELECTOR 0 is: %s"), *KeySelectorArray[0]->GetName());
		UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key NAME 0 is: %s"), *LoadedGame->KeyNameArray[0]);

		//KeySelectorArray[0]->SetNoKeySpecifiedText(FText::FromString(LoadedGame->SavedKey));
		//UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key NAME is: %s"), *LoadedGame->SavedKey);

		/*for(int i = 0; i < KeySelectorArray.Num(); i++)
		{
			KeySelectorArray[i]->SetNoKeySpecifiedText(FText::FromString(LoadedGame->KeyNameArray[i]));
			UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key SELECTOR is: %s"), *KeySelectorArray[i]->GetName());
			UE_LOG(LogTemp, Warning, TEXT("C_SettingsControlWidegt: Key NAME is: %s"), *LoadedGame->KeyNameArray[i]);
		}*/

		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		//UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->PlayerLocation.ToString());
	}
}