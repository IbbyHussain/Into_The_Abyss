// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_UW_EKeyHint.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_UW_EKeyHint : public UUserWidget
{
	GENERATED_BODY()
public:

	UC_UW_EKeyHint(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UTextBlock* TXTEKeyHint;

	UFUNCTION()
	void BecomeVisible();

	UFUNCTION()
	void BecomeInVisible();

	UFUNCTION()
	void InVisible();

	//Widget Animation
	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* FadeInAnimation;

	UWidgetAnimation* FadeOutAnimation;

	// Keyword
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keyword")
	FString KeyWord;
	
};
