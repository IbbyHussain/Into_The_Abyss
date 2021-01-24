
#include "C_BTTask_AttackTarget.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"

UC_BTTask_AttackTarget::UC_BTTask_AttackTarget(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UC_BTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	// Calls attack function
	AIController->PawnBasicAttack();

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
