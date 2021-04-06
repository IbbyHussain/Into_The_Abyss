// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_SettingsGameOptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_SettingsGameOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BackButton;

	UFUNCTION()
		void BackButtonClicked();

	class AC_PlayerHUD2* HUD;
	
};
