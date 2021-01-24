// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_AIHealthBar.generated.h"


UCLASS()
class MYPROJECT_API UC_AIHealthBar : public UUserWidget
{
	GENERATED_BODY()

	UC_AIHealthBar(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget));
	class UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget));
	class UProgressBar* AIHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget));
	class UTextBlock* AIName;

	void UpdateAIName(FString Name);

	void UpdateAIHealth(float Health);

	void AIHealthBarVisible();

	void AIHealthBarInVisible();
	
};
