// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"

UC_SettingsWidget::UC_SettingsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_SettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	 HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	VideoButton->OnClicked.AddDynamic(this, &UC_SettingsWidget::VideoButtonClicked);
	ControlsButton->OnClicked.AddDynamic(this, &UC_SettingsWidget::ControlsButtonClicked);
	SoundButton->OnClicked.AddDynamic(this, &UC_SettingsWidget::SoundButtonClicked);
	GameOptionsButton->OnClicked.AddDynamic(this, &UC_SettingsWidget::GameOptionsButtonClicked);

}

void UC_SettingsWidget::VideoButtonClicked()
{
	if(HUD)
	{
		HUD->CreateVideoSettingsWidget();
		RemoveFromParent();
	}
}

void UC_SettingsWidget::ControlsButtonClicked()
{
	if (HUD)
	{
		HUD->CreateControlsSettingsWidget();
		RemoveFromParent();
	}
}

void UC_SettingsWidget::SoundButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSoundSettingsWidget();
		RemoveFromParent();
	}
}

void UC_SettingsWidget::GameOptionsButtonClicked()
{
	if (HUD)
	{
		HUD->CreateGameOptionsSettingsWidget();
		RemoveFromParent();
	}
}
