// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_QuestObjectivesWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_QuestObjectivesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// A referenec to the quest that this widget should use.
	// This referenece is used to bind the text fields in this widget to the struct data in the AC_BaseQuest class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	class AC_BaseQuest* Quest;

	virtual void NativeConstruct() override;

	// clears current objective add adds new one
	void UpdateObjectives();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* List;
	
};
