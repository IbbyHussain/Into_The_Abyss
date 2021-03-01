// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_QuestTurnInWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_QuestTurnInWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	// A referenec to the quest that this widget should use.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	class AC_BaseQuest* Quest;

	
};
