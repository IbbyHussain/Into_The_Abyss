// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AIHealthBar.h"

UC_AIHealthBar::UC_AIHealthBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_AIHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	AIName->SetText(FText::FromString(""));

	AIHealthBar->SetVisibility(ESlateVisibility::Hidden);

	FLinearColor HealthBarColor = FColor(255, 0, 0);
	AIHealthBar->SetFillColorAndOpacity(HealthBarColor);
	
}

void UC_AIHealthBar::UpdateAIName(FString Name)
{
	AIName->SetText(FText::FromString(Name));
}

void UC_AIHealthBar::UpdateAIHealth(float Health)
{
	AIHealthBar->SetPercent(Health);
}

void UC_AIHealthBar::AIHealthBarVisible()
{
	AIHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void UC_AIHealthBar::AIHealthBarInVisible()
{
	AIHealthBar->SetVisibility(ESlateVisibility::Hidden);
}