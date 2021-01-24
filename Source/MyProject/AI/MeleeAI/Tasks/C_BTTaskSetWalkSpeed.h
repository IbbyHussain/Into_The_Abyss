// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTaskSetWalkSpeed.generated.h"

UCLASS()
class MYPROJECT_API UC_BTTaskSetWalkSpeed : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

		UC_BTTaskSetWalkSpeed(FObjectInitializer const& ObjectInitializer);

public:

	// The speed to set
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float Speed;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);
	
};
