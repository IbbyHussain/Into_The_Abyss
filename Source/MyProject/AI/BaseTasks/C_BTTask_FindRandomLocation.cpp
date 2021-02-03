// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include"BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"

#include "DrawDebugHelpers.h"

UC_BTTask_FindRandomLocation::UC_BTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Find Random Location");

	SearchRadius = 1500.0f;
}

EBTNodeResult::Type UC_BTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	// Get AI Controller and BaseAI
	auto const AIController = Cast<AAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();

	// Get AI location to use as the start position
	FVector const StartLocation = BaseAI->GetActorLocation();
	FNavLocation Location;

	// Get the Navigation System and generate a random location within the Nav Mesh
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	NavigationSystem->GetRandomPointInNavigableRadius(StartLocation, SearchRadius, Location, nullptr);
	
		// Set the BlackBoards value so that its updated in the BehaviorTree
	UAIBlueprintHelperLibrary::GetBlackboard(BaseAI)->SetValueAsVector(BB_MeleeAIKeys::RandomLocation, Location.Location);

		// DRAW A DEBUG SPHERE AT LOCATION IF GREATER THAN 50 UNITS AWAY
	DrawDebugSphere(GetWorld(), Location.Location, 35.0f, 5, FColor::Yellow, false, 4.0f);
	

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
