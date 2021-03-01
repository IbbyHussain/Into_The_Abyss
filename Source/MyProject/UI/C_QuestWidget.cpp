// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuestWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/Quest System/C_BaseQuest.h"

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
	RemoveFromParent();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;

	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerCharacter->BroadcastCanTrade();

	AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (HUD)
	{
		HUD->CreateObjectiveWidget(Quest);
	}

	Quest->bHasBeenAccepted = true;

}

// when clicked reject button
void UC_QuestWidget::RejectQuest()
{
	RemoveFromParent();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;

	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerCharacter->BroadcastCanTrade();
}