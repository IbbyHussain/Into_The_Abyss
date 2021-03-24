// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AvailableQuest.h"
#include "MyProject/Quest System/C_BaseQuest.h"
#include "Components/Image.h"

void UC_AvailableQuest::NativeConstruct()
{
	Super::NativeConstruct();
}

void UC_AvailableQuest::SetQuestMarkerImage(class AC_BaseQuest* Quest)
{
	if(Quest->PreRequisiteQuest)
	{
		//UE_LOG(LogTemp, Error, TEXT("Available Quest: there was a pre requisite"));

		QuestIMG->SetBrushFromTexture(PreRequisiteQuestTexture);
	}

	else
	{
		//UE_LOG(LogTemp, Error, TEXT("Available Quest: there was NOT a pre requisite"));

		QuestIMG->SetBrushFromTexture(DefaultQuestTexture);
	}
}

void UC_AvailableQuest::CheckQuestMarkerImage(class AC_BaseQuest* Quest)
{
	if (Quest->PreRequisiteQuest &&  Quest->PreRequisiteQuest->bIsCompleted)
	{
		//UE_LOG(LogTemp, Error, TEXT("Available Quest: pre requisite IS COMPLETE"));

		QuestIMG->SetBrushFromTexture(DefaultQuestTexture);
	}
}