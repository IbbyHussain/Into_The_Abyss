// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsControlsWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h" // not needed
#include "GameFramework/InputSettings.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/InputKeySelector.h"

void UC_SettingsControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsControlsWidget::BackButtonClicked);

	Input = UInputSettings::GetInputSettings();

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

void UC_SettingsControlsWidget::RemapActionBinding(FName ActionName)
{

}

void UC_SettingsControlsWidget::JumpButtonClicked(FInputChord InputChord)
{
	TArray <FInputActionKeyMapping> OutMappings;

	Input->GetActionMappingByName(FName("Jump"), OutMappings);

	for (auto i : OutMappings)
	{
		Input->RemoveActionMapping(i, false);
	}

	FInputActionKeyMapping NewMapping;
	
	InputChord.bShift = NewMapping.bShift;
	InputChord.bCtrl = NewMapping.bCtrl;
	InputChord.bAlt = NewMapping.bAlt;
	InputChord.bCmd = NewMapping.bCmd;

	NewMapping.ActionName = "Jump";

	Input->AddActionMapping(NewMapping, true);
	
	Input->SaveKeyMappings();
	Input->SaveConfig();
}


