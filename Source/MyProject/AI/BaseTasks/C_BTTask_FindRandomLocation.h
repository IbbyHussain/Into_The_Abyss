// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/UObjectGlobals.h"
#include "C_BTTask_FindRandomLocation.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API UC_BTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer);

private:

	// AI's Search radius 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float SearchRadius;

protected:

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);
	
};
