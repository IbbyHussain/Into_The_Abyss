// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTaskGetWanderLocation.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include"BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include"MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTaskGetWanderLocation::UC_BTTaskGetWanderLocation(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Find Wander Location");
}

EBTNodeResult::Type UC_BTTaskGetWanderLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	FNavLocation Location;
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	NavigationSystem->GetRandomPointInNavigableRadius(AIController->GetBlackBoard()->GetValueAsVector(OriginLocation.SelectedKeyName), 400.0f, Location, nullptr);

	AIController->GetBlackBoard()->SetValueAsVector(TargetLocation.SelectedKeyName, Location.Location);

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

// This allows us to pass values to the task in BT, letting us select from the values in the Blackboard
//AIController->GetBlackBoard()->GetValueAsVector(OriginLocation.SelectedKeyName)