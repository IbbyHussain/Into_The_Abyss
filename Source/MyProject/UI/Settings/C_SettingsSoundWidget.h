// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_SettingsSoundWidget.generated.h"

class USlider;

UCLASS()
class MYPROJECT_API UC_SettingsSoundWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

	UFUNCTION()
	void BackButtonClicked();

	class AC_PlayerHUD2* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* MasterSlider;

	UFUNCTION()
	void OnMasterSliderChanged(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* MusicSlider;

	UFUNCTION()
	void OnMusicSliderChanged(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sliders")
	class USoundMix* MasterSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sliders")
	class USoundClass* MasterSoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sliders")
	class USoundMix* MusicSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sliders")
	class USoundClass* MusicSoundClass;
};
