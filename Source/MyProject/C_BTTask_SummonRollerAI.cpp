// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_SummonRollerAI.h"

EBTNodeResult::Type UC_BTTask_SummonRollerAI::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	/*auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	// Calls attack function
	AIController->PawnBasicAttack();*/

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}