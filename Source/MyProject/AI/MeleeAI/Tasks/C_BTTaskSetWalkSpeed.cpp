// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTTaskSetWalkSpeed.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"

UC_BTTaskSetWalkSpeed::UC_BTTaskSetWalkSpeed(FObjectInitializer const& ObjectInitializer)
{
	// Set the nodes name
	NodeName = TEXT("Set Max Walk Speed");
}

EBTNodeResult::Type UC_BTTaskSetWalkSpeed::ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory)
{
	auto const AIController = Cast<AC_MeleeAIController>(Owner.GetAIOwner());
	auto const BaseAI = AIController->GetCharacter();

	// Sets speed 
	BaseAI->GetCharacterMovement()->MaxWalkSpeed = Speed;

	// Finish Task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
