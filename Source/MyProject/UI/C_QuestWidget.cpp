// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuestWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UC_QuestWidget::UC_QuestWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_QuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AcceptButton->OnClicked.AddDynamic(this, &UC_QuestWidget::AcceptQuest);
	RejectButton->OnClicked.AddDynamic(this, &UC_QuestWidget::RejectQuest);

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

// When clicked accept button
void UC_QuestWidget::AcceptQuest()
{
	// Add quest to quest log

	RemoveFromParent();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}

// when clicked reject button
void UC_QuestWidget::RejectQuest()
{
	RemoveFromParent();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}