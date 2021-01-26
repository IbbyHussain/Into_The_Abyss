
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "C_BTTask_AttackTarget.generated.h"

UCLASS()
class MYPROJECT_API UC_BTTask_AttackTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTask_AttackTarget(FObjectInitializer const& ObjectInitializer);

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);

private:
	
};
