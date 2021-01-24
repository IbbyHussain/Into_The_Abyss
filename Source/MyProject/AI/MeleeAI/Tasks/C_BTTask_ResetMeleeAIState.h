
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTask_ResetMeleeAIState.generated.h"


UCLASS()
class MYPROJECT_API UC_BTTask_ResetMeleeAIState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTask_ResetMeleeAIState(FObjectInitializer const& ObjectInitializer);

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector State;
	
};
