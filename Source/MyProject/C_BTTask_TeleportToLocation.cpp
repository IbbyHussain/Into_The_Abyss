// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTask_TeleportToLocation.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Creatures/C_SummonerAI.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UC_BTTask_TeleportToLocation::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetPawn();
	
	AC_SummonerAI* SummonerAI = Cast<AC_SummonerAI>(BaseAI);

	FTransform PlayerTransform;
	FVector TeleportLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	PlayerTransform.SetLocation(FVector(TeleportLocation.X, TeleportLocation.Y, TeleportLocation.Z - 90.0f));
	PlayerTransform.SetRotation(FRotator(90, 0, 0).Quaternion());
	PlayerTransform.SetScale3D(FVector(1.0f));

	DrawDebugCircle(GetWorld(), PlayerTransform.ToMatrixWithScale(), 250.0f, 76, FColor::Purple, true, 10.0f, 10, 2.0f, true);

	float RandomAngle = UKismetMathLibrary::RandomFloatInRange(0, 1) * PI * 2.0f;

	float X = UKismetMathLibrary::Cos(RandomAngle) * 250.0f;
	float Y = UKismetMathLibrary::Sin(RandomAngle) * 250.0f;

	UE_LOG(LogTemp, Warn)
	
	SummonerAI->SetActorLocation(FVector(X, Y, PlayerTransform.GetLocation().Z + 120.0f));
	SummonerAI->TeleportToLocationEffects();

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}