
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/UObjectGlobals.h"
#include "C_BTTask_GetPlayerLocation.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API UC_BTTask_GetPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UC_BTTask_GetPlayerLocation(FObjectInitializer const& ObjectInitializer);

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory);

	// The distance between the AI and the player. The AI will keep this distance from the player
	UPROPERTY(EditInstanceOnly, category = "AI")
	float Distance;

	// The speed of the AI
	UPROPERTY(EditInstanceOnly, category = "AI")
	float WalkSpeed;

	void SetFocus(AActor* AIActor, AAIController* AIController);
	
};
