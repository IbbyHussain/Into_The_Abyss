// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsSoundWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"


void UC_SettingsSoundWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsSoundWidget::BackButtonClicked);

	MasterSlider->OnValueChanged.AddDynamic(this, &UC_SettingsSoundWidget::OnMasterSliderChanged);
	MusicSlider->OnValueChanged.AddDynamic(this, &UC_SettingsSoundWidget::OnMusicSliderChanged);
}

void UC_SettingsSoundWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}

void UC_SettingsSoundWidget::OnMasterSliderChanged(float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MasterSoundClass, Value, 1.0f, 0.1f, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);
}

void UC_SettingsSoundWidget::OnMusicSliderChanged(float Value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MusicSoundMix, MusicSoundClass, Value, 1.0f, 0.1f, true);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MusicSoundMix);
}