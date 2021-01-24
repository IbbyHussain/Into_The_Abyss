// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_AITradeWindow.generated.h"

class UC_ItemWidget;
class AC_BaseTraderAI;

UCLASS()
class MYPROJECT_API UC_AITradeWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	UC_AITradeWindow(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	// Close the widget

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	TArray<UC_ItemWidget*> ItemArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	UC_ItemWidget* Item1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	UC_ItemWidget* Item2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	UC_ItemWidget* Item3;

	// PTR so that the values in the widget are determined by the AI class, and can be set in editor per instance
	AC_BaseTraderAI* TraderAI;

	void ValidateTraderAI();

	UFUNCTION()
	void CloseWidget();
};
