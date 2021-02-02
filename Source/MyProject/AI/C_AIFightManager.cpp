
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

	MaxAIInArray = AIArray.Num();

	NumOfDeadAI = 1;
}

// At the start of the game 
AC_MeleeAI* AC_AIFightManager::GenerateMapElements()
{
	// returning a value in the map will cancel out of the loop therefroe only populating map by one value
	// For all melee AI
	for (auto i : AIArray)
	{
		// Add them to the map, with a random grade (grade determines the priority of if they can attack)
		AIMap.Add(i, UKismetMathLibrary::RandomFloatInRange(1.0f, 5.0f));
	}

	return nullptr;
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

		// Dereference pointer to get value in map
		float Foundi = *(AIMap.Find(i));

		// Add both values multiplied to the map. This will be AI's grade
		AIMap.Add(i, Foundi * NormilisedValue);
	}

	return nullptr;
}

AC_MeleeAI* AC_AIFightManager::GradeByAttackFrequency()
{
	for (auto x : AIArray)
	{
		// May need to remove this condition to make more random 
		/*if(x->AITime > 9.0f)
		{
			if (x->AITime > 24.0f)
			{
				x->AITime = 24.0f;
			}

			UE_LOG(LogTemp, Warning, TEXT("Time was: %f"), x->AITime);

			float Time = x->AITime / 2.0f;

			int IntTime = int(Time);

			UE_LOG(LogTemp, Warning, TEXT("INT Time was: %d"), IntTime);

			float Foundz = *(AIMap.Find(x));
			UE_LOG(LogTemp, Warning, TEXT("Found Value BEFORE for loop was: %f"), Foundz);

			for (int i = 0; i < IntTime; i++)
			{
				float FoundY = *(AIMap.Find(x));
				AIMap.Add(x, FoundY + 0.5);
				UE_LOG(LogTemp, Warning, TEXT("LOOP RUN"));
			}

			float Foundx = *(AIMap.Find(x));
			UE_LOG(LogTemp, Warning, TEXT("Found Value AFTER for loop was: %f"), Foundx);
		}

		float FoundZ = *(AIMap.Find(x));
		AIMap.Add(x, FoundZ - 0.5f);*/

		if (x->AITime > 24.0f)
		{
			x->AITime = 24.0f;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Time was: %f"), x->AITime);

		float Time = x->AITime / 2.0f;

		int IntTime = int(Time);

		//UE_LOG(LogTemp, Warning, TEXT("INT Time was: %d"), IntTime);

		float Foundz = *(AIMap.Find(x));
		//UE_LOG(LogTemp, Warning, TEXT("Found Value BEFORE for loop was: %f"), Foundz);

		for (int i = 0; i < IntTime; i++)
		{
			float FoundY = *(AIMap.Find(x));
			AIMap.Add(x, FoundY + 0.2);
			//UE_LOG(LogTemp, Warning, TEXT("LOOP RUN"));
		}

		float Foundx = *(AIMap.Find(x));
		//UE_LOG(LogTemp, Warning, TEXT("Found Value AFTER for loop was: %f"), Foundx);

	}

	return nullptr;
}

void AC_AIFightManager::DestroyManager()
{

	// As item index starts at -1 numofdeadAI must start at 1
	// Stores the ID of the AI that has died then removes that AI from array after loop finishes.
	int32 ItemIndex = -1;
	for (int32 Index = 0; Index < AIArray.Num(); Index++)
	{
		if(AIArray[Index]->bHasDied)
		{
			NumOfDeadAI++;
			ItemIndex = Index;
			break;
		}
	}

	if(AIArray.IsValidIndex(ItemIndex))
	{
		AIArray.RemoveAt(ItemIndex);
	}

	//UE_LOG(LogTemp, Error, TEXT("NUMOFDEADAI ==: %d"), NumOfDeadAI);

	// If all AI are dead destroy this manager
	if(MaxAIInArray == NumOfDeadAI)
	{
		//UE_LOG(LogTemp, Error, TEXT("ALL AI ARE DEAD"));

		Destroy();
	}
}