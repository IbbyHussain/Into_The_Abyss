// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuestObjectivesWidget.h"
#include "Components/VerticalBox.h"
#include "MyProject/Quest System/C_BaseQuest.h"
#include "MyProject/UI/C_PlayerHUD2.h"

void UC_QuestObjectivesWidget::NativeConstruct()
{
	UpdateObjectives();
}

void UC_QuestObjectivesWidget::UpdateObjectives()
{
	List->ClearChildren();

	for (auto i : Quest->ObjectivesArray)
	{
		AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (HUD)
		{
			HUD->CreateSingleObjectiveWidget(List, i.ObjectiveDescription, i.bIsObjectiveComplete);
		}
	}
}
