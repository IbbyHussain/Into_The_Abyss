
#include "C_AIFightManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/Gameplaystatics.h"
#include "Math/Vector.h"



// Sets default values
AC_AIFightManager::AC_AIFightManager()
{

}

// Called when the game starts or when spawned
void AC_AIFightManager::BeginPlay()
{
	Super::BeginPlay();
}

// At the start of the game 
void AC_AIFightManager::GenerateMapElements()
{
	// For all melee AI
	for (auto i : AIArray)
	{
		// Add them to the map, with a random grade (grade determines the priority of if they can attack)
		AIMap.Add(i, UKismetMathLibrary::RandomFloatInRange(1.0f, 5.0f));
	}
}

void AC_AIFightManager::ResetAIGrade(AC_MeleeAI* MeleeAI)
{
	auto const AIController = Cast<AC_MeleeAIController>(UAIBlueprintHelperLibrary::GetAIController(MeleeAI));

	if (AIController)
	{
		// Allows AI to attack
		AIController->AIAttack();

		// Resets AI Grade so can't attack (temp)
		AIMap.Add(MeleeAI, UKismetMathLibrary::RandomFloatInRange(1.0f, 5.0f));
	}
}

void AC_AIFightManager::RecalculateGrade()
{
	GradeByLocation();
}

// Calculates a grade based on AI's location to player
AC_MeleeAI* AC_AIFightManager::GradeByLocation()
{
	for (auto i : AIArray)
	{
		// Get the and player AI forward vector
		FVector AIForwardVector = i->GetActorForwardVector();
		FVector PlayerForwardVector = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorForwardVector();

		// Dot between those vectors so that we can evaluate if an AI is more infront of the player compared to another AI
		float  AIDotProduct = AIForwardVector.DotProduct(AIForwardVector, PlayerForwardVector) * -1.0f;

		// Normilise value (makes it easier to work with)
		float NormilisedValue = UKismetMathLibrary::NormalizeToRange(AIDotProduct, -1.0f, 1.0f) + 0.5f;

		// Dereference pointer to get value at ptr location
		float Foundi = *(AIMap.Find(i));

		// Multiply both values and add to map, this value will be added to AI's grade
		AIMap.Add(i, Foundi * NormilisedValue);

		UE_LOG(LogTemp, Error, TEXT("Valid"));

		return i;
	}

	UE_LOG(LogTemp, Error, TEXT("NONE"));

	return nullptr;
}

AC_MeleeAI* AC_AIFightManager::GradeByAttackFrequency()
{
	for (auto x : AIArray)
	{

	}

	return nullptr;
}
