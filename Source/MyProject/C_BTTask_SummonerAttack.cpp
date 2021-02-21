// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_SummonerAttack.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "Kismet/KismetSystemLibrary.h"

UC_BTTask_SummonerAttack::UC_BTTask_SummonerAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = ("Summoner Attack");
}

EBTNodeResult::Type UC_BTTask_SummonerAttack::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	// Calls attack function
	AIController->PawnBasicAttack();

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}