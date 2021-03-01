// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_QuestObjectiveItemsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_QuestObjectiveItemsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// A referenec to the quest that this widget should use.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	class AC_BaseQuest* Quest;

	// The boolean used to toggle the checkbox used in this widget, when the objective is completed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	bool bIsObjectiveComplete;

	// The simplified objective text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	FText ObjectiveText;
	
};
