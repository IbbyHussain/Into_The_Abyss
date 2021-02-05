// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_Savage_Jump.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "MyProject/AI/EnglishEnemies/C_SavageAI.h"

UC_BTTask_Savage_Jump::UC_BTTask_Savage_Jump(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Jump");
}

EBTNodeResult::Type UC_BTTask_Savage_Jump::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();

	auto const MeleeAI = Cast<AC_SavageAI>(BaseAI);

	if (MeleeAI)
	{
		MeleeAI->JumpStart();

		// Finish Task with success
		FinishLatentTask(Owner, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}


	// Finish Task with FAIL
	FinishLatentTask(Owner, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
