// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_ResetMeleeAIState.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include"MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"

UC_BTTask_ResetMeleeAIState::UC_BTTask_ResetMeleeAIState(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Reset State");
}

EBTNodeResult::Type UC_BTTask_ResetMeleeAIState::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	AIController->AIStatesController = EAIStates::HOLDING;

	uint8 Holding = (uint8)EAIStates::HOLDING;
	AIController->GetBlackBoard()->SetValueAsEnum(State.SelectedKeyName, Holding);

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
