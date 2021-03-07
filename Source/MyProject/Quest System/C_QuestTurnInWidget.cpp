// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuestTurnInWidget.h"
#include "MyProject/Quest System/C_BaseQuest.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Quest System/C_QuestObjectivesWidget.h"
#include "MyProject/AI/QuestNPC/C_QuestNPC.h"
#include "TimerManager.h"

void UC_QuestTurnInWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TurnInButton->OnClicked.AddDynamic(this, &UC_QuestTurnInWidget::TurnInButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UC_QuestTurnInWidget::CancelButtonClicked);

	AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	GetWorld()->GetTimerManager().SetTimer(CameraHandle, this, &UC_QuestTurnInWidget::EnableUIInput, 1.0f);

	for (auto i : Quest->ObjectivesArray)
	{
		HUD->CreateQuestObjectiveItems(Quest, ObjectivesList, i.ObjectiveDescription, i.bIsObjectiveComplete);

		if (bIsQuestComplete())
		{
			TurnInButton->SetVisibility(ESlateVisibility::Visible);
		}

		else
		{
			TurnInButton->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UC_QuestTurnInWidget::EnableUIInput()
{
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
}

bool UC_QuestTurnInWidget::bIsQuestComplete()
{
	bool AllObjectivesComplete = true;

	for (auto i : Quest->ObjectivesArray)
	{
		if (!i.bIsObjectiveComplete)
		{
			AllObjectivesComplete = false;
		}
	}

	return AllObjectivesComplete;
}

void UC_QuestTurnInWidget::TurnInButtonClicked()
{
	AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if(HUD)
	{
		if(HUD->QuestObjectivesWidget)
		{
			HUD->QuestObjectivesWidget->UpdateObjectives();
			HUD->ClearObjectives();

			UE_LOG(LogTemp, Error, TEXT("UPDATED OBJECTIVES"));

			Quest->bIsCompleted = true;

			RemoveFromParent();
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;

			AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
			PlayerCharacter->BroadcastCanTrade();

			// Adds souls as a reward
			if (PlayerCharacter->NumberOfSouls < 30)
			{
				// Increments and Sends a signal to HUD widget to update text
				PlayerCharacter->NumberOfSouls += Quest->QuestSoulsReward;

				if(PlayerCharacter->NumberOfSouls > 30)
				{
					PlayerCharacter->NumberOfSouls = 30;
				}

				PlayerCharacter->UpdatenumberOfSouls.Broadcast(PlayerCharacter->NumberOfSouls);

				// Saves the value
				PlayerCharacter->SaveNumberOfSouls();
			}


			QuestNPC->RemoveKeyHint_Implementation();
			QuestNPC->bCanTalkAI = false;
			QuestNPC->bShowEKeyHint = false;
		}
	}
}

void UC_QuestTurnInWidget::CancelButtonClicked()
{
	RemoveFromParent();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;

	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerCharacter->BroadcastCanTrade();
}
