// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_GetPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include"BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include"MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"

UC_BTTask_GetPlayerLocation::UC_BTTask_GetPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UC_BTTask_GetPlayerLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	AActor* AI = Owner.GetAIOwner();

	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(PlayerCharacter->GetActorLocation(), AI->GetActorLocation());

	FVector RandomUnitVector = (UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Direction, 60.0f)) * Distance;

	FVector a = PlayerCharacter->GetActorLocation() + RandomUnitVector;

	FNavLocation Location;

	// Get the Navigation System and generate a random location within the Nav Mesh
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	NavigationSystem->GetRandomPointInNavigableRadius(a, 50.0f, Location, nullptr);

	// Set the vector to the random point in the navigable radius
	AIController->GetBlackBoard()->SetValueAsVector(BB_MeleeAIKeys::TargetLocation, Location.Location);

	SetFocus(AI, AIController);

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

void UC_BTTask_GetPlayerLocation::SetFocus(AActor* AIActor, AAIController* AIController)
{
	FVector StartLocation = AIActor->GetActorLocation();
	FVector EndLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(AIActor);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Camera, Params);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.5f);

	if(Hit.Actor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		AIController->SetFocus(Hit.GetActor());

		UE_LOG(LogTemp, Log, TEXT("Valid: set focus"));
	}
}
