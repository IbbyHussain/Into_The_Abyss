// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "C_PlayerHUD2.generated.h"

class UC_WeaponWheel;
class UC_CrossBowBoltTracker;

UCLASS()
class MYPROJECT_API AC_PlayerHUD2 : public AHUD
{
	GENERATED_BODY()

	AC_PlayerHUD2();

public:

	// General

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void HideAllElements();

	UFUNCTION(BlueprintCallable)
	void ShowAllElements();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UC_HUDWidget2* HUDWidget;

	class UC_UW_EKeyHint* EKeyHintWidget;

	//class UC_MiniMap* MiniMapWidget;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,  Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> EKeyHintWidgetClass;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<UUserWidget> MiniMapWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void AddEKeyHintToViewport();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void MakeEKeyHintVisible();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void MakeEKeyHintInVisible();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void EKeyHintInVisible();

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void PlayExitAreaAnimationHUD();

	UFUNCTION()
	void PlayBreathBarFadeInAnimationHUD();

	UFUNCTION()
	void PlayBreathBarFadeOutAnimationHUD();

	UFUNCTION()
	void HUDBreathBarVisible();

	UFUNCTION()
	void HUDBreathBarInVisible();

	FString SetEKeyHintText(FString HUDKeyword);

	void InstantlyInVisible();

	//WeaponWheel

	UC_WeaponWheel* WeaponWheelWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UC_WeaponWheel> WeaponWheelWidgetClass;

	void AddWeaponWheelToViewport();

	void MakeWeaponWheelVisible();

	void MakeWeaponWheelInVisible();

	UFUNCTION(BlueprintCallable)
	void UnlockWeaponWheelAbilities(bool bUnlockSword, bool bUnlockMagic, bool bUnlockCrossbow);

	//Input Modes

	APlayerController* PlayerController;

	void SetInputModeGameAndUI();

	void SetInputModeGameOnly();

	//MiniMap
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_MiniMap> MiniMapWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	class UC_MiniMap* MiniMapWidget;

	//Crossbow bolt tracker

	void UpdateCrossbowBoltTracker(UC_CrossBowBoltTracker* CrossBowBoltTrackerWidget, int32 NumOfBolts);

	bool bFadeOut;

	//AI Health and Name

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_AIHealthBar> AIHealthWidgetClass;

	class UC_AIHealthBar* AIHealthBarWidget;

	void SetAIName(FString AIName);

	void SetAIHealth(float AIHealth);

	void MakeAIHealthBarVisible();

	void MakeAIHealthBarInVisible();

	// Pickup widgets

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_PickupWidget> PickupWidgetClass;

	class UC_PickupWidget* PickupWidget;

	void CreatePickupWidget(float Time);

	void PlayPickupWidgetFadeOut();

	void DestroyPickupWidget();

	void DisplayHealthImage();

	void DisplayStaminaImage();

	void DisplayManaImage();

	void DisplayDamageImage();

	FTimerHandle PickupWidgetHandle;

	FTimerHandle DestroyPickupWidgetHandle;

	void ClearPickupTimer(float Time);

	bool bFading;

	// Player Death

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_PlayerDeathWidget> PlayerDeathWidgetClass;

	class UC_PlayerDeathWidget* PlayerDeathWidget;

	void CreatePlayerDeathWidget();

	void DestroyPlayerDeathWidget();

	// AI Trading

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_AITradeWindow> AITradeWidgetClass;

	class UC_AITradeWindow* AITradeWidget;

	void CreateTradingWindow(TSubclassOf<class UC_AITradeWindow> AITradeWindowWidgetClass);

	void DestroyTradingWindow(TSubclassOf<class UC_AITradeWindow> AITradeWindowWidgetClass);

	void UpdateCurrency();

	// NPC Questing

	void CreateQuestWidget(class AC_BaseQuest* QuestRef);

	void DestroyQuestWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_QuestWidget> QuestWidgetClass;

	UPROPERTY()
	class UC_QuestWidget* QuestWidget;

	// NPC Questing - Objective widget

	void CreateObjectiveWidget(class AC_BaseQuest* QuestRef);

	void DestroyObjectiveWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_QuestObjectivesWidget> QuestObjectivesWidgetClass;

	class UC_QuestObjectivesWidget* QuestObjectivesWidget;

	void UpdateObjectives();

	void ClearObjectives();

	// NPC Questing - Objective Single widget

	void CreateSingleObjectiveWidget(class UVerticalBox* VerticalBoxRef, FText ObjectiveDescription, bool bIsObjectiveComplete);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SingleObjectiveWidget> SingleObjectivesWidgetClass;

	class UC_SingleObjectiveWidget* SingleObjectivesWidget;

	// NPC Questing - Quest Turn In

	void CreateQuestTurnInWidget(AC_BaseQuest* QuestRef, class AC_QuestNPC* NPCRef, class AC_TheLabLevel_ManagerClass* ManagerClassRef);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_QuestTurnInWidget> QuestTurnInWidgetClass;

	class UC_QuestTurnInWidget* QuestTurnInWidget;

	// NPC Questing - Quest Objective Items

	void CreateQuestObjectiveItems(AC_BaseQuest* QuestRef, class UScrollBox* ScrollBox, FText Text, bool bIsComplete);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_QuestObjectiveItemsWidget> QuestObjectiveItemsWidgetClass;

	class UC_QuestObjectiveItemsWidget* QuestObjectiveItemsWidget;

	// NPC - Talk Window

	void CreateTalkWindow(TArray<FText> SpeechArray, bool bClose);

	void DestroyTalkWindow();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_AITalkWindow> TalkWindowWidgetClass;

	class UC_AITalkWindow* TalkWindow;

	// Misc - Sercurity Camera

	void CreateCameraWidget();

	void DestroyCameraWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SercurityCameraWidget> CameraWidgetClass;

	class UC_SercurityCameraWidget* CameraWidget;

	// Settings Menu

	void CreateSettingsWidget();

	void DestroySettingsWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SettingsWidget> SettingsWidgetClass;

	class UC_SettingsWidget* SettingsWidget;

	// Video Settings

	void CreateVideoSettingsWidget();

	void DestroyVideoSettingsWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SettingsVideoWidget> VideoSettingsWidgetClass;

	class UC_SettingsVideoWidget* VideoSettingsWidget;

	// Sound Settings

	void CreateSoundSettingsWidget();

	void DestroySoundSettingsWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SettingsSoundWidget> SoundSettingsWidgetClass;

	class UC_SettingsSoundWidget* SoundSettingsWidget;

	// Controls

	void CreateControlsSettingsWidget();

	void DestroyControlsSettingsWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SettingsControlsWidget> ControlSettingsWidgetClass;

	class UC_SettingsControlsWidget* ControlSettingsWidget;

	// Game Options

	void CreateGameOptionsSettingsWidget();

	void DestroyGameOptionsSettingsWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UC_SettingsGameOptionsWidget> GameOptionsSettingsWidgetClass;

	class UC_SettingsGameOptionsWidget* GameOptionsSettingsWidget;

	// MISC

	void HideLockedWidgets(bool bMagic, bool bHealth, bool bSouls);

	UFUNCTION(BlueprintCallable)
	void HideSouls();

	UFUNCTION(BlueprintCallable)
	void ShowSouls();

};
