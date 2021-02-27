// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_HUDWidget2.generated.h"

class UProgressBar;
class UTextBlock;
class UImage;

UCLASS()
class MYPROJECT_API UC_HUDWidget2 : public UUserWidget
{
	GENERATED_BODY()
	
	UC_HUDWidget2(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

	// The quest widget is added to this canvas pannel
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* QuestWidgetHolder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* PROHealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* PROStaminaBar;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* PROMagicBar;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* PROBreathBar;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UC_MiniMap* MiniMap;
	// Currency counter

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TXTSoulCounter;

	FString Souls;

	float WidgetStamina;

	class AC_PlayerCharacter* Player;

	//Update Stats Functions
	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void UpdateHealth();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void UpdateStamina();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void UpdateMagic();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void UpdateBreath();

	UFUNCTION()
	void UpdateCurrency(int num);

	//Widget Animation
	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* ExitAreaAnimation;

	UWidgetAnimation* BeginPlayAnimation;

	UWidgetAnimation* BreathBarFadeInAnimation;

	UWidgetAnimation* BreathBarFadeOutAnimation;

	UFUNCTION()
	void PlayBreathBarFadeInAnimation();

	UFUNCTION()
	void PlayBreathBarFadeOutAnimation();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
	void PlayExitAreaAnimation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UImage* BlackImage;

	//Helper Functions
	UFUNCTION()
	void BreathBarVisible();

	UFUNCTION()
	void BreathBarInVisible();

	class AC_PlayerCharacter* PlayerCharacter;

};
