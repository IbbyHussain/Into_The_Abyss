// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTService_GetAIHealth.h"
#include "AIController.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "MyProject/AI/C_BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyProject/Components/C_HealthComponent.h"

UC_BTService_GetAIHealth::UC_BTService_GetAIHealth(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "Get AI Health";

    bNotifyBecomeRelevant = true;    // necessarily!!!
    //bNotifyCeaseRelevant = true;

    Interval = 0.5f;
    RandomDeviation = 0.f;
}

void UC_BTService_GetAIHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    UBlackboardComponent* CurrentBlackboard = OwnerComp.GetBlackboardComponent();

    // Get AI Controller and BaseAI
    auto const AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    auto const AI = AIController->GetPawn();

    AC_BaseAI* BaseAI = Cast<AC_BaseAI>(AI);

    if (BaseAI)
    {
        CurrentBlackboard->SetValueAsFloat(Health.SelectedKeyName, BaseAI->HealthComp->Health);

        UE_LOG(LogTemp, Error, TEXT("Health is: %f"), BaseAI->HealthComp->Health);
    }
}
