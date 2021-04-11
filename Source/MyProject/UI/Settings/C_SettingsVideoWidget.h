// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/Misc/C_BaseSaveGame.h"
#include "C_SettingsVideoWidget.generated.h"


class UButton;

UCLASS()
class MYPROJECT_API UC_SettingsVideoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UFUNCTION()
	void BackButtonClicked();

	class AC_PlayerHUD2* HUD;

	class APlayerController* PlayerController;

	// Resolution settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SDButton;

	UFUNCTION()
	void SDButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* HDButton;

	UFUNCTION()
	void HDButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* FHDButton;

	UFUNCTION()
	void FHDButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QHDButton;

	UFUNCTION()
	void QHDButtonClicked();

	// Anti Aliasing settings

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LowButton;

	UFUNCTION()
	void LowButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MediumButton;

	UFUNCTION()
	void MediumButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* HighButton;

	UFUNCTION()
	void HighButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EpicButton;

	UFUNCTION()
	void EpicButtonClicked();

	// Shadow Quality 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SQLowButton;

	UFUNCTION()
	void SQLowButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SQMediumButton;

	UFUNCTION()
	void SQMediumButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SQHighButton;

	UFUNCTION()
	void SQHighButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SQEpicButton;

	UFUNCTION()
	void SQEpicButtonClicked();

	// Texture Quality 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TQLowButton;

	UFUNCTION()
	void TQLowButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TQMediumButton;

	UFUNCTION()
	void TQMediumButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TQHighButton;

	UFUNCTION()
	void TQHighButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TQEpicButton;

	UFUNCTION()
	void TQEpicButtonClicked();

	// Motion Blur

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MBLowButton;

	UFUNCTION()
	void MBLowButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MBMediumButton;

	UFUNCTION()
	void MBMediumButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MBHighButton;

	UFUNCTION()
	void MBHighButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MBEpicButton;

	UFUNCTION()
	void MBEpicButtonClicked();

	void SaveVideoOption(TEnumAsByte<EVideoOption> Option, int32 Index);

	void LoadVideoOption();

	void CheckForVideoOption(UC_BaseSaveGame* SaveGame, int32 Index);
};
