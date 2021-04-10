// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsSoundWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Misc/C_BaseSaveGame.h"


void UC_SettingsSoundWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsSoundWidget::BackButtonClicked);

	MasterSlider->OnValueChanged.AddDynamic(this, &UC_SettingsSoundWidget::OnMasterSliderChanged);
	MusicSlider->OnValueChanged.AddDynamic(this, &UC_SettingsSoundWidget::OnMusicSliderChanged);

	LoadSliderValue();
}

void UC_SettingsSoundWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();

		SaveSliderValue();
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

void UC_SettingsSoundWidget::SaveSliderValue()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		SaveGameInstance->MasterSliderValue = MasterSlider->GetValue();
		SaveGameInstance->MusicSliderValue = MusicSlider->GetValue();

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Sound"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("UC_SettingsSoundWidget: Save Succeeded SOUND"));
		}
	}
}

// Call this on begin play in a delegate ?
void UC_SettingsSoundWidget::LoadSliderValue()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Sound"), 0)))
	{
		MasterSlider->SetValue(LoadedGame->MasterSliderValue);
		MusicSlider->SetValue(LoadedGame->MusicSliderValue);

		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MasterSoundClass, LoadedGame->MasterSliderValue, 1.0f, 0.1f, true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MusicSoundMix, MusicSoundClass, LoadedGame->MusicSliderValue, 1.0f, 0.1f, true);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), MusicSoundMix);
	}
}