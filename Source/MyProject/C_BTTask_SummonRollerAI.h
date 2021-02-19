// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTask_SummonRollerAI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_BTTask_SummonRollerAI : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);
};
