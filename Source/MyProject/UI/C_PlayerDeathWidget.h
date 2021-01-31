// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_PlayerDeathWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_PlayerDeathWidget : public UUserWidget
{
	GENERATED_BODY()

	UC_PlayerDeathWidget(const FObjectInitializer& ObjectInitializer);

private:

	virtual void NativeConstruct() override;

	void FadeIn();

	//Widget Animation
	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* FadeInAnimation;
	
};
