// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "C_BTService_GetAIHealth.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_BTService_GetAIHealth : public UBTService_BlackboardBase
{
	GENERATED_BODY()

		UC_BTService_GetAIHealth(const FObjectInitializer& ObjectInitializer);
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory,float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		FBlackboardKeySelector  Health;
};
