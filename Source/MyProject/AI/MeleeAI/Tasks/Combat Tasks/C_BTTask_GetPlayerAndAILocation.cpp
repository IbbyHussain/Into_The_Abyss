// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_GetPlayerAndAILocation.h"
#include "Kismet/Gameplaystatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include"BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTask_GetPlayerAndAILocation::UC_BTTask_GetPlayerAndAILocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = ("Get Player and AI Locations");
}

EBTNodeResult::Type UC_BTTask_GetPlayerAndAILocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	// Get refernec to AI controller and AI
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();

	// Get current location of AI and Player
	FVector AILocationVector = BaseAI->GetActorLocation();
	FVector PlayerLocationVector = (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetActorLocation();

	// Set the blackboard key selectors to AI and Player location
	AIController->GetBlackBoard()->SetValueAsVector(OriginalLocation.SelectedKeyName, AILocationVector);
	AIController->GetBlackBoard()->SetValueAsVector(PlayerLocation.SelectedKeyName, PlayerLocationVector);

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
