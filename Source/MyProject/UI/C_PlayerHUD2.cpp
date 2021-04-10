// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerHUD2.h"
#include "C_HUDWidget2.h"
#include "C_UW_EKeyHint.h"
#include "C_WeaponWheel.h"
#include "MyProject/UI/C_AITalkWindow.h"
#include "MyProject/UI/C_MiniMap.h"
#include "MyProject/UI/C_CrossBowBoltTracker.h"
#include "MyProject/UI/C_AIHealthBar.h"
#include "MyProject/UI/C_PickupWidget.h"
#include "MyProject/UI/C_AITradeWindow.h"
#include "MyProject/UI/C_PlayerDeathWidget.h"
#include "MyProject/UI/C_QuestWidget.h"
#include "MyProject/Quest System/C_QuestObjectivesWidget.h"
#include "MyProject/Quest System/C_SingleObjectiveWidget.h"
#include "MyProject/Quest System/C_QuestTurnInWidget.h"
#include "MyProject/C_QuestObjectiveItemsWidget.h"
#include "TimerManager.h"
#include "Components/ScrollBox.h"
#include "MyProject/AI/QuestNPC/C_QuestNPC.h"
#include "MyProject/UI/C_SercurityCameraWidget.h"
#include "MyProject/UI/C_SettingsWidget.h"
#include "MyProject/UI/Settings/C_SettingsVideoWidget.h"
#include "MyProject/UI/Settings/C_SettingsSoundWidget.h"
#include "MyProject/C_SettingsControlsWidget.h"
#include "MyProject/C_SettingsGameOptionsWidget.h"
//CONSTRUCTOR 
AC_PlayerHUD2::AC_PlayerHUD2()
{

}

// DRAW HUD
void AC_PlayerHUD2::DrawHUD()
{
	Super::DrawHUD();
}

//
void AC_PlayerHUD2::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (WidgetClass)
	{
		HUDWidget = CreateWidget<UC_HUDWidget2>(GetWorld(), WidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();

		}
	}

	if (EKeyHintWidgetClass)
	{
		EKeyHintWidget = CreateWidget<UC_UW_EKeyHint>(GetWorld(), EKeyHintWidgetClass);
		if (EKeyHintWidget)
		{
			EKeyHintWidget->AddToViewport();
		}
	}

	//Add AI Health Bar and Name widget to class
	if (AIHealthWidgetClass)
	{
		AIHealthBarWidget = CreateWidget<UC_AIHealthBar>(GetWorld(), AIHealthWidgetClass);
		if (AIHealthBarWidget)
		{
			AIHealthBarWidget->AddToViewport();
		}
	}

	AddWeaponWheelToViewport();
}


// General

void AC_PlayerHUD2::HideAllElements()
{
	HUDWidget->PROHealthBar->SetVisibility(ESlateVisibility::Hidden);
	HUDWidget->PROStaminaBar->SetVisibility(ESlateVisibility::Hidden);
	HUDWidget->PROMagicBar->SetVisibility(ESlateVisibility::Hidden);
	HUDWidget->PROBreathBar->SetVisibility(ESlateVisibility::Hidden);
	HUDWidget->MiniMap->SetVisibility(ESlateVisibility::Hidden);
	//HUDWidget->
	//HUDWidget->PROHealthBar->SetVisibility(ESlateVisibility::Hidden);
}

void AC_PlayerHUD2::ShowAllElements()
{
	HUDWidget->PROHealthBar->SetVisibility(ESlateVisibility::Visible);
	HUDWidget->PROStaminaBar->SetVisibility(ESlateVisibility::Visible);
	HUDWidget->PROMagicBar->SetVisibility(ESlateVisibility::Visible);
	HUDWidget->PROBreathBar->SetVisibility(ESlateVisibility::Visible);
	HUDWidget->MiniMap->SetVisibility(ESlateVisibility::Visible);
}

//Function to add EkeyHint Widget to the viewport
void AC_PlayerHUD2::AddEKeyHintToViewport()
{
	if(EKeyHintWidgetClass)
	{
		EKeyHintWidget = CreateWidget<UC_UW_EKeyHint>(GetWorld(), EKeyHintWidgetClass);
		if (EKeyHintWidget)
		{
			EKeyHintWidget->AddToViewport();
		}
	}
}

//Makes EKeyHint Widget Visible
void AC_PlayerHUD2::MakeEKeyHintVisible()
{
	if(EKeyHintWidget)
	{
		EKeyHintWidget->BecomeVisible();
	}
}

//Makes EKeyHint Widget InVisible
void AC_PlayerHUD2::MakeEKeyHintInVisible()
{
	if (EKeyHintWidget)
	{
		EKeyHintWidget->BecomeInVisible();
	}
}

void AC_PlayerHUD2::PlayExitAreaAnimationHUD()
{
	if (HUDWidget)
	{
		HUDWidget->PlayExitAreaAnimation();
	}
}

void AC_PlayerHUD2::EKeyHintInVisible()
{
	if (EKeyHintWidget)
	{
		EKeyHintWidget->InVisible();
	}
}

void AC_PlayerHUD2::HUDBreathBarVisible()
{
	if(HUDWidget)
	{
		HUDWidget->BreathBarVisible();
	}
}

void AC_PlayerHUD2::HUDBreathBarInVisible()
{
	if (HUDWidget)
	{
		HUDWidget->BreathBarInVisible();
	}
}

void AC_PlayerHUD2::PlayBreathBarFadeInAnimationHUD()
{
	if (HUDWidget)
	{
		HUDWidget->PlayBreathBarFadeInAnimation();
	}
}
	
void AC_PlayerHUD2::PlayBreathBarFadeOutAnimationHUD()
{
	if(HUDWidget)
	{
		HUDWidget->PlayBreathBarFadeOutAnimation();
	}
}

FString AC_PlayerHUD2::SetEKeyHintText(FString HUDKeyword)
{
	if (EKeyHintWidget)
	{
		EKeyHintWidget->TXTEKeyHint->SetText(FText::FromString("Press E to " + HUDKeyword));

		return HUDKeyword;
	}
	
	return TEXT("");
}

void AC_PlayerHUD2::InstantlyInVisible()
{
	if (EKeyHintWidget)
	{
		EKeyHintWidget->InVisible();
	}
}

// Crossbow bolt tracker

void AC_PlayerHUD2::UpdateCrossbowBoltTracker(UC_CrossBowBoltTracker* CrossBowBoltTrackerWidget, int32 NumOfBolts)
{
	if(CrossBowBoltTrackerWidget)
	{
		// Updates the number of bolts from the crossbowbolt tracker widget
		CrossBowBoltTrackerWidget->UpdateNumberOfBolts(NumOfBolts);
	}
}

//Adds Weapon Wheel to the viewport
void AC_PlayerHUD2::AddWeaponWheelToViewport()
{
	if(WeaponWheelWidgetClass)
	{
		WeaponWheelWidget = CreateWidget<UC_WeaponWheel>(GetWorld(), WeaponWheelWidgetClass);
		if (WeaponWheelWidget)
		{
			WeaponWheelWidget->AddToViewport();
		}
	}
}

//WeaponWheel Visible
void AC_PlayerHUD2::MakeWeaponWheelVisible()
{
	if(WeaponWheelWidget)
	{
		WeaponWheelWidget->PlayFadeInAnimation();
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->bShowMouseCursor = true;
	}
}

//WeaponWheel InVisible
void AC_PlayerHUD2::MakeWeaponWheelInVisible()
{
	if (WeaponWheelWidget)
	{
		WeaponWheelWidget->PlayFadeOutAnimation();
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void AC_PlayerHUD2::UnlockWeaponWheelAbilities(bool bUnlockSword, bool bUnlockMagic, bool bUnlockCrossbow)
{
	if(WeaponWheelWidgetClass && WeaponWheelWidget)
	{
		// If the player has unlocked an ability allow them to use it else make it locked
		bUnlockSword ? WeaponWheelWidget->bUnLockedSword = true : WeaponWheelWidget->bUnLockedSword = false;

		bUnlockMagic ? WeaponWheelWidget->bUnlockedMagic = true : WeaponWheelWidget->bUnlockedMagic = false;
		
		bUnlockCrossbow ? WeaponWheelWidget->bUnlockedCrossBow = true : WeaponWheelWidget->bUnlockedCrossBow = false;
	}
}

//Sets the input mode mode to game and UI
void AC_PlayerHUD2::SetInputModeGameAndUI()
{

}

//Sets the input mode mode to UI
void AC_PlayerHUD2::SetInputModeGameOnly()
{

}

void AC_PlayerHUD2::SetAIName(FString AIName)
{
	AIHealthBarWidget->UpdateAIName(AIName);
}

void AC_PlayerHUD2::SetAIHealth(float AIHealth)
{
	AIHealthBarWidget->UpdateAIHealth(AIHealth);
}

void AC_PlayerHUD2::MakeAIHealthBarVisible()
{
	AIHealthBarWidget->AIHealthBarVisible();
}

void AC_PlayerHUD2::MakeAIHealthBarInVisible()
{
	AIHealthBarWidget->AIHealthBarInVisible();
}

// Pickup widgets

void AC_PlayerHUD2::CreatePickupWidget(float Time)
{
	// A widget is only created if the pickup widget handle is not active
	if (!(GetWorldTimerManager().IsTimerActive(PickupWidgetHandle)))
	{
		if (PickupWidgetClass)
		{
			// Creates widget
			PickupWidget = CreateWidget<UC_PickupWidget>(GetWorld(), PickupWidgetClass);
			if (PickupWidget)
			{
				// renders widget and plays fade in animation
				PickupWidget->AddToViewport();
				PickupWidget->FadeIn();

				//UE_LOG(LogTemp, Log, TEXT("Play Fade In"));

				// Sets timer to play fade out (after fade in has finished)
				GetWorldTimerManager().SetTimer(PickupWidgetHandle, this, &AC_PlayerHUD2::PlayPickupWidgetFadeOut, Time, false);
				//UE_LOG(LogTemp, Log, TEXT("Start Fade out Timer"));
			}
		}
	}
}

// Used if player overlaps multiple pickups (stops multiple fade in animations from playing and them not being destroyed after)
void AC_PlayerHUD2::ClearPickupTimer(float Time)
{
	// If player overlaps with anothe rpickup while pickup is fading out will not play any more animations or display pickup widgets
	if(GetWorldTimerManager().IsTimerActive(PickupWidgetHandle) || GetWorldTimerManager().IsTimerActive(DestroyPickupWidgetHandle))
	{
		// Clears timer then starts timer again. So iuf player interacts with multiple pickups multiple times clears the timer.
		//but then starts again so afer will play fade out animation. Called when the player interacts with a pickup
		GetWorldTimerManager().ClearTimer(PickupWidgetHandle);

		GetWorldTimerManager().SetTimer(PickupWidgetHandle, this, &AC_PlayerHUD2::PlayPickupWidgetFadeOut, Time, false);
	}
}

// Destroys the widget from screen
void AC_PlayerHUD2::DestroyPickupWidget()
{
	if(PickupWidgetClass)
	{
		if (PickupWidget)
		{
			PickupWidget->RemoveFromParent();
			//UE_LOG(LogTemp, Log, TEXT("Destroyed Widget"));
		}
	}
}

void AC_PlayerHUD2::PlayPickupWidgetFadeOut()
{
	if (PickupWidget)
	{
		// If the timer is still active
		if(GetWorldTimerManager().IsTimerActive(PickupWidgetHandle))
		{
			bFading = true;
			// play fade out animation
			PickupWidget->FadeOut();
			//UE_LOG(LogTemp, Log, TEXT("Play Fade Out"));

			// After fade out animation has finished destroy it from screen.
			GetWorldTimerManager().SetTimer(DestroyPickupWidgetHandle, this, &AC_PlayerHUD2::DestroyPickupWidget, 0.15f, false);
			//UE_LOG(LogTemp, Log, TEXT("Start Destroy Timer"));
		}
	}
}

void AC_PlayerHUD2::DisplayHealthImage()
{
	if (PickupWidget)
	{
		PickupWidget->DisplayHealth();
	}
}

void AC_PlayerHUD2::DisplayStaminaImage()
{
	if (PickupWidget)
	{
		PickupWidget->DisplayStamina();
	}
}

void AC_PlayerHUD2::DisplayManaImage()
{
	if (PickupWidget)
	{
		PickupWidget->DisplayMana();
	}
}

// Used when player takes damage
void AC_PlayerHUD2::DisplayDamageImage()
{
	if(PickupWidget)
	{
		PickupWidget->DisplayDamage();
	}
}

// Player Death

void AC_PlayerHUD2::CreatePlayerDeathWidget()
{
	// A widget is only created if the pickup widget handle is not active

	if (PlayerDeathWidgetClass)
	{
		// Creates widget
		PlayerDeathWidget = CreateWidget<UC_PlayerDeathWidget>(GetWorld(),PlayerDeathWidgetClass);
		if (PlayerDeathWidget)
		{
			// renders widget
			PlayerDeathWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroyPlayerDeathWidget()
{
	if (PlayerDeathWidgetClass)
	{
		if (PlayerDeathWidget)
		{
			PlayerDeathWidget->RemoveFromParent();
		}
	}
}

// AI Trading

void AC_PlayerHUD2::CreateTradingWindow(TSubclassOf<class UC_AITradeWindow> AITradeWindowWidgetClass)
{
	if(AITradeWindowWidgetClass)
	{
		AITradeWidget = CreateWidget<UC_AITradeWindow>(GetWorld(), AITradeWindowWidgetClass);
		if(AITradeWidget)
		{
			AITradeWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::UpdateCurrency()
{
	HUDWidget->UpdateCurrency(1);
}

void AC_PlayerHUD2::DestroyTradingWindow(TSubclassOf<class UC_AITradeWindow> AITradeWindowWidgetClass)
{
	if (AITradeWindowWidgetClass)
	{
		if (AITradeWidget)
		{
			AITradeWidget->RemoveFromParent();
		}
	}
}

// NPC Questing

void AC_PlayerHUD2::CreateQuestWidget(class AC_BaseQuest* QuestRef)
{
	if (QuestWidgetClass)
	{
		QuestWidget = CreateWidget<UC_QuestWidget>(GetWorld(), QuestWidgetClass);
		if (QuestWidget)
		{
			QuestWidget->Quest = QuestRef;
			QuestWidget->AddToViewport();
			QuestWidget->SetDesiredSizeInViewport(FVector2D(500.0f, 800.0f));
		}
	}
}

void AC_PlayerHUD2::DestroyQuestWidget()
{
	if (QuestWidgetClass)
	{
		if (QuestWidget)
		{
			QuestWidget->RemoveFromParent(); // acess violation reading location
		}
	}
}

void AC_PlayerHUD2::CreateObjectiveWidget(AC_BaseQuest* QuestRef)
{
	if (QuestObjectivesWidgetClass)
	{
		QuestObjectivesWidget = CreateWidget<UC_QuestObjectivesWidget>(GetWorld(), QuestObjectivesWidgetClass);
		if (QuestObjectivesWidget)
		{
			QuestObjectivesWidget->Quest = QuestRef;
			QuestObjectivesWidget->AddToViewport();
			//QuestObjectivesWidget->SetDesiredSizeInViewport(FVector2D(500.0f, 800.0f));
			//QuestObjectivesWidget->SetPositionInViewport(FVector2D(500.0f, 250.0f));
		}
	}
}

void AC_PlayerHUD2::DestroyObjectiveWidget()
{
	if (QuestObjectivesWidgetClass)
	{
		if (QuestObjectivesWidget)
		{
			QuestObjectivesWidget->RemoveFromParent();
		}
	}
}

void AC_PlayerHUD2::UpdateObjectives()
{
	if(QuestObjectivesWidget)
	{
		QuestObjectivesWidget->UpdateObjectives();
	}
}

void AC_PlayerHUD2::ClearObjectives()
{
	if(QuestObjectivesWidget)
	{
		QuestObjectivesWidget->ClearObjectives();
	}
}

void AC_PlayerHUD2::CreateSingleObjectiveWidget(class UVerticalBox* VerticalBoxRef, FText ObjectiveDescription, bool bIsObjectiveComplete)
{
	if (SingleObjectivesWidgetClass)
	{
		SingleObjectivesWidget = CreateWidget<UC_SingleObjectiveWidget>(GetWorld(), SingleObjectivesWidgetClass);
		if (SingleObjectivesWidget)
		{
			VerticalBoxRef->AddChild(SingleObjectivesWidget);

			SingleObjectivesWidget->SingleObjectiveDescription = ObjectiveDescription;
			SingleObjectivesWidget->bSingleIsComplete = bIsObjectiveComplete;
		}
	}
}

void AC_PlayerHUD2::CreateQuestTurnInWidget(AC_BaseQuest* QuestRef, class AC_QuestNPC* NPCRef, class AC_TheLabLevel_ManagerClass* ManagerClassRef)
{
	if (QuestTurnInWidgetClass)
	{
		QuestTurnInWidget = CreateWidget<UC_QuestTurnInWidget>(GetWorld(), QuestTurnInWidgetClass);
		if (QuestTurnInWidget)
		{
			QuestTurnInWidget->Quest = QuestRef;
			QuestTurnInWidget->QuestNPC = NPCRef;
			QuestTurnInWidget->ManagerClass = ManagerClassRef;
			QuestTurnInWidget->AddToViewport();
			QuestTurnInWidget->SetDesiredSizeInViewport(FVector2D(500.0f, 800.0f));
		}
	}
}

void AC_PlayerHUD2::CreateQuestObjectiveItems(AC_BaseQuest* QuestRef, class UScrollBox* ScrollBox, FText Text, bool bIsComplete)
{
	if (QuestObjectiveItemsWidgetClass)
	{
		QuestObjectiveItemsWidget = CreateWidget<UC_QuestObjectiveItemsWidget>(GetWorld(), QuestObjectiveItemsWidgetClass);
		if (QuestObjectiveItemsWidget)
		{
			QuestObjectiveItemsWidget->Quest = QuestRef;
			ScrollBox->AddChild(QuestObjectiveItemsWidget);
			QuestObjectiveItemsWidget->ObjectiveText = Text;
			QuestObjectiveItemsWidget->bIsObjectiveComplete = bIsComplete;
		}
	}
}

// NPC Talk Window

void AC_PlayerHUD2::CreateTalkWindow(TArray<FText> SpeechArray)
{
	if (TalkWindowWidgetClass)
	{
		TalkWindow = CreateWidget<UC_AITalkWindow>(GetWorld(), TalkWindowWidgetClass);
		if (TalkWindow)
		{

			for (int i = 0; i < SpeechArray.Num(); i++)
			{
				TalkWindow->AISpeechArray.Add(SpeechArray[i]);
			}

			TalkWindow->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroyTalkWindow()
{
	if (TalkWindowWidgetClass)
	{
		if (TalkWindow)
		{
			TalkWindow->RemoveFromParent();
		}
	}
}

// Camera

void AC_PlayerHUD2::CreateCameraWidget()
{
	if (CameraWidgetClass)
	{
		CameraWidget = CreateWidget<UC_SercurityCameraWidget>(GetWorld(), CameraWidgetClass);
		if (CameraWidget)
		{
			CameraWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroyCameraWidget()
{
	if (CameraWidgetClass)
	{
		if (CameraWidget)
		{
			CameraWidget->RemoveFromParent();
		}
	}
}

// Settings

void AC_PlayerHUD2::CreateSettingsWidget()
{
	if (SettingsWidgetClass)
	{
		SettingsWidget = CreateWidget<UC_SettingsWidget>(GetWorld(), SettingsWidgetClass);
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroySettingsWidget()
{
	if (SettingsWidgetClass)
	{
		if (SettingsWidget)
		{
			SettingsWidget->RemoveFromParent();
		}
	}
}

// Video

void AC_PlayerHUD2::CreateVideoSettingsWidget()
{
	if (VideoSettingsWidgetClass)
	{
		VideoSettingsWidget = CreateWidget<UC_SettingsVideoWidget>(GetWorld(), VideoSettingsWidgetClass);
		if (VideoSettingsWidget)
		{
			VideoSettingsWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroyVideoSettingsWidget()
{
	if (VideoSettingsWidgetClass)
	{
		if (VideoSettingsWidget)
		{
			VideoSettingsWidget->RemoveFromParent();
		}
	}
}

// Sound

void AC_PlayerHUD2::CreateSoundSettingsWidget()
{
	if (SoundSettingsWidgetClass)
	{
		SoundSettingsWidget = CreateWidget<UC_SettingsSoundWidget>(GetWorld(), SoundSettingsWidgetClass);
		if (SoundSettingsWidget)
		{
			SoundSettingsWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroySoundSettingsWidget()
{
	if (SoundSettingsWidgetClass)
	{
		if (SoundSettingsWidget)
		{
			SoundSettingsWidget->RemoveFromParent();
		}
	}
}

// Controls

void AC_PlayerHUD2::CreateControlsSettingsWidget()
{
	if (ControlSettingsWidgetClass)
	{
		ControlSettingsWidget = CreateWidget<UC_SettingsControlsWidget>(GetWorld(), ControlSettingsWidgetClass);
		if (ControlSettingsWidget)
		{
			ControlSettingsWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroyControlsSettingsWidget()
{
	if (ControlSettingsWidgetClass)
	{
		if (ControlSettingsWidget)
		{
			ControlSettingsWidget->RemoveFromParent();
		}
	}
}

// Game Options

void AC_PlayerHUD2::CreateGameOptionsSettingsWidget()
{
	if (GameOptionsSettingsWidgetClass)
	{
		GameOptionsSettingsWidget = CreateWidget<UC_SettingsGameOptionsWidget>(GetWorld(), GameOptionsSettingsWidgetClass);
		if (GameOptionsSettingsWidget)
		{
			GameOptionsSettingsWidget->AddToViewport();
		}
	}
}

void AC_PlayerHUD2::DestroyGameOptionsSettingsWidget()
{
	if (GameOptionsSettingsWidgetClass)
	{
		if (GameOptionsSettingsWidget)
		{
			GameOptionsSettingsWidget->RemoveFromParent();
		}
	}
}

// MISC

void AC_PlayerHUD2::HideLockedWidgets(bool bMagic, bool bHealth, bool bSouls)
{
	if(bMagic)
	{
		HUDWidget->PROMagicBar->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if(bHealth)
	{
		HUDWidget->PROHealthBar->SetVisibility(ESlateVisibility::Hidden);
	}

	if(bSouls)
	{
		HUDWidget->SoulsImage->SetVisibility(ESlateVisibility::Hidden);
		HUDWidget->TXTSoulCounter->SetVisibility(ESlateVisibility::Hidden);
	}

}

void AC_PlayerHUD2::HideSouls()
{
	HUDWidget->SoulsImage->SetVisibility(ESlateVisibility::Hidden);
	HUDWidget->TXTSoulCounter->SetVisibility(ESlateVisibility::Hidden);
}

void AC_PlayerHUD2::ShowSouls()
{
	HUDWidget->SoulsImage->SetVisibility(ESlateVisibility::Visible);
	HUDWidget->TXTSoulCounter->SetVisibility(ESlateVisibility::Visible);
}