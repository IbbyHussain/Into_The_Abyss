// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsGameOptionsWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"

void UC_SettingsGameOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsGameOptionsWidget::BackButtonClicked);
}

void UC_SettingsGameOptionsWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}