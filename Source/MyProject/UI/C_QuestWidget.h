// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_QuestWidget.generated.h"

UCLASS()
class MYPROJECT_API UC_QuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UC_QuestWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* AcceptButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* RejectButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* ObjectivesList;

	UFUNCTION()
	void AcceptQuest();

	UFUNCTION()
	void RejectQuest();

	APlayerController* PlayerController;

	// A referenec to the quest that this widget should use.
	// This referenece is used to bind the text fields in this widget to the struct data in the AC_BaseQuest class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	class AC_BaseQuest* Quest;
	
};
