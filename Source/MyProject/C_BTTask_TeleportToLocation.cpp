// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_TeleportToLocation.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Creatures/C_SummonerAI.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UC_BTTask_TeleportToLocation::UC_BTTask_TeleportToLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = ("Teleport to location");

	Radius = 500.0f;
}

EBTNodeResult::Type UC_BTTask_TeleportToLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();
	
	AC_SummonerAI* SummonerAI = Cast<AC_SummonerAI>(BaseAI);

	// Get player location
	FVector TeleportLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	// Get player transfrom, will be the centre of the circle
	FTransform PlayerTransform;
	PlayerTransform.SetLocation(FVector(TeleportLocation.X, TeleportLocation.Y, TeleportLocation.Z - 90.0f));
	PlayerTransform.SetRotation(FRotator(90, 0, 0).Quaternion());
	PlayerTransform.SetScale3D(FVector(1.0f));


	// Draws a debug cirlce, circle used as the area the summoner should teleport to.
	DrawDebugCircle(GetWorld(), PlayerTransform.ToMatrixWithScale(), Radius, 76, FColor::Purple, true, 10.0f, 10, 2.0f, true);

	// Get a random angle within the circle
	float Theeta = UKismetMathLibrary::RandomFloatInRange(0, 360) * PI * 2.0f;

	// Get a X and Y co-ordinate on the circumference
	float X = UKismetMathLibrary::DegCos(Theeta) * Radius + TeleportLocation.X;
	float Y = UKismetMathLibrary::DegSin(Theeta) * Radius + TeleportLocation.Y;
	
	// Set summoner Location to that point on circumference
	SummonerAI->SetActorLocation(FVector(X, Y, PlayerTransform.GetLocation().Z + 100.0f));
	SummonerAI->TeleportToLocationEffects();

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}