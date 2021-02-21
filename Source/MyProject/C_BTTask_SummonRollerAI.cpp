// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_SummonRollerAI.h"
#include "MyProject/AI/Creatures/C_SummonerAI.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"

EBTNodeResult::Type UC_BTTask_SummonRollerAI::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();

	auto const SummonerAI = Cast<AC_SummonerAI>(BaseAI);

	if (SummonerAI)
	{
		SummonerAI->SummonerSpecialAttack();

		// Finish Task with success
		FinishLatentTask(Owner, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}


	// Finish Task with FAIL
	FinishLatentTask(Owner, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}