// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/UObjectGlobals.h"
#include "C_BTTask_FocusOnTarget.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API UC_BTTask_FocusOnTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTask_FocusOnTarget(FObjectInitializer const& ObjectInitializer);

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);
	
};
