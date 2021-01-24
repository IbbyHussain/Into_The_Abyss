
#include "C_BTTask_FocusOnTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include"MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"

#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UC_BTTask_FocusOnTarget::UC_BTTask_FocusOnTarget(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Focus On Target");
}

EBTNodeResult::Type UC_BTTask_FocusOnTarget::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());

	// AI will focus on current target (rotate to face)
	AIController->SetFocus(AIController->CurrentTarget);

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
