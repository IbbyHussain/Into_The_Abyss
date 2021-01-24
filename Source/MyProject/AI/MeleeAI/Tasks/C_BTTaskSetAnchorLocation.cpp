// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTaskSetAnchorLocation.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include"BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyProject/AI/C_BaseAI.h"

UC_BTTaskSetAnchorLocation::UC_BTTaskSetAnchorLocation(FObjectInitializer const& ObjectInitializer)
{

}

EBTNodeResult::Type UC_BTTaskSetAnchorLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{

	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();

	AIController->GetBlackBoard()->SetValueAsVector(TargetLocation.SelectedKeyName, BaseAI->GetActorLocation()); //TargetLocation.SelectedKeyName

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
