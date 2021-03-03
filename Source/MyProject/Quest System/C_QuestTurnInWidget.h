// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_QuestTurnInWidget.generated.h"

UCLASS()
class MYPROJECT_API UC_QuestTurnInWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	// A referenec to the quest that this widget should use.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	class AC_BaseQuest* Quest;

	// A reference to the quest NPC that this widget should use.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	class AC_QuestNPC* QuestNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* ObjectivesList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TurnInButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CancelButton;

	bool bIsQuestComplete();

	UFUNCTION()
	void TurnInButtonClicked();

	UFUNCTION()
	void CancelButtonClicked();
	
	APlayerController* PlayerController;
};
