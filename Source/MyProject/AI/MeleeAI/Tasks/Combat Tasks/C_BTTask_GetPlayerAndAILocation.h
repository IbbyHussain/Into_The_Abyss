// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTask_GetPlayerAndAILocation.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_BTTask_GetPlayerAndAILocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTask_GetPlayerAndAILocation(FObjectInitializer const& ObjectInitializer);

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector PlayerLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector OriginalLocation;

};
