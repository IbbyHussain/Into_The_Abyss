// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_BlackFadeInWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_BlackFadeInWidget : public UUserWidget
{
	GENERATED_BODY()

	UC_BlackFadeInWidget(const FObjectInitializer& ObjectInitializer);

public:

	virtual void NativeConstruct() override;

	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* BlackFadeAnimation;

	
};
