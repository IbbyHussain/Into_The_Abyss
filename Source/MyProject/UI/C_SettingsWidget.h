// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_SettingsWidget.generated.h"

UCLASS()
class MYPROJECT_API UC_SettingsWidget : public UUserWidget
{
	GENERATED_BODY()

	UC_SettingsWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

	class AC_PlayerHUD2* HUD;

	// Video 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* VideoButton;

	UFUNCTION()
	void VideoButtonClicked();

	// Sound

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SoundButton;

	UFUNCTION()
	void SoundButtonClicked();

	// Controls

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ControlsButton;

	UFUNCTION()
	void ControlsButtonClicked();
};
