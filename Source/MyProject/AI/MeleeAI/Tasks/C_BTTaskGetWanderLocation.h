// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTaskGetWanderLocation.generated.h"

UCLASS()
class MYPROJECT_API UC_BTTaskGetWanderLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTaskGetWanderLocation(FObjectInitializer const& ObjectInitializer);

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float WanderRadius;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector  OriginLocation;
	
};
