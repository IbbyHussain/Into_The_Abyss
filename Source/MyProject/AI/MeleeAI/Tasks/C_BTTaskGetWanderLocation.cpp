// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTaskGetWanderLocation.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"

#include "DrawDebugHelpers.h"

UC_BTTaskGetWanderLocation::UC_BTTaskGetWanderLocation(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Find Wander Location");

	WanderRadius = 350.0f;
}

EBTNodeResult::Type UC_BTTaskGetWanderLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();

	// The initial Location of the AI
	FVector OriginalLocation = BaseAI->GetActorLocation();

	// DRAW DEBUG SPHERE AT ORIGINAL LOCATION
	DrawDebugSphere(GetWorld(), OriginalLocation, 35.0f, 25, FColor::Blue, false, 4.0f);

	// Navigation system setup
	FNavLocation Location;
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	// Gets a random point in a navigable radius
	NavigationSystem->GetRandomPointInNavigableRadius(AIController->GetBlackBoard()->GetValueAsVector(OriginLocation.SelectedKeyName), WanderRadius, Location, nullptr);

	// Get the distance from the original location to target location
	FVector dist = OriginalLocation - Location.Location;
	float Distance = dist.Size();

	//UE_LOG(LogTemp, Log, TEXT("Distance was: %f"), Distance);

	if(Distance > (WanderRadius - 50.0f))
	{
		AIController->GetBlackBoard()->SetValueAsVector(TargetLocation.SelectedKeyName, Location.Location);

		// DRAW A DEBUG SPHERE AT LOCATION IF GREATER THAN 50 UNITS AWAY
		DrawDebugSphere(GetWorld(), Location.Location, 35.0f, 25, FColor::Green, false, 4.0f);

		// Finish Task with success
		FinishLatentTask(Owner, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	else
	{
		// DRAW A DEBUG SPHERE AT LOCATION IF NOT GREATER THAN 50 UNITS AWAY
		DrawDebugSphere(GetWorld(), Location.Location, 35.0f, 25, FColor::Red, false, 4.0f);
	}


	// Finish Task with FAIL
	FinishLatentTask(Owner, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

// This allows us to pass values to the task in BT, letting us select from the values in the Blackboard
//AIController->GetBlackBoard()->GetValueAsVector(OriginLocation.SelectedKeyName)