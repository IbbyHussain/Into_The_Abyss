
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_AIFightManager.generated.h"

UCLASS()
class MYPROJECT_API AC_AIFightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_AIFightManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	TArray<class AC_MeleeAI*> AIArray;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	TMap<class AC_MeleeAI*, float> AIMap;

	UFUNCTION(BlueprintCallable)
	void GenerateMapElements();

	UFUNCTION(BlueprintCallable)
	void ResetAIGrade(AC_MeleeAI* MeleeAI);

	// Behaviour conditions

	// recalculates grade before attacking
	UFUNCTION(BlueprintCallable)
	void RecalculateGrade();

	// A behaviour condition based on the AI's location to the player. If behind lower grade and if infront higher grade.
	UFUNCTION(BlueprintCallable)
	AC_MeleeAI* GradeByLocation();

	// A behaviour condition based on the AI's time since they last attacked. If they dont attack their grade increases.
	UFUNCTION(BlueprintCallable)
	AC_MeleeAI* GradeByAttackFrequency();
};
