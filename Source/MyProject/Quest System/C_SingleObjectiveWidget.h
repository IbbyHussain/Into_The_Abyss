// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_SingleObjectiveWidget.generated.h"

class UTextBlock;

UCLASS()
class MYPROJECT_API UC_SingleObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

	UC_SingleObjectiveWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* IsComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ObjectiveDescription;

	// The variable which will be binded to the text block.
	// Passed as a parameter when this widget is created so its value can be changed to the Objective description inside the struct (in quest class)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	FText SingleObjectiveDescription;

	// same as above ^^^
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	bool bSingleIsComplete;
};
