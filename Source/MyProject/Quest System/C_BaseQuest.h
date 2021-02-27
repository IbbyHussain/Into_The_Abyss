
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseQuest.generated.h"

USTRUCT()
struct FObjectiveData
{
	GENERATED_BODY() 
public:
	FName ObjectiveDescription;

	bool bIsObjectiveComplete;

	// Which enemy type to kill
	AActor* ObjectiveTarget;

	// e.g number of targets
	int32 ObjectiveNumber;

	// The enums value
	EObjectiveTypes ObjectiveTypes;

	FObjectiveData()
	{

	}

};


// The type of objectives that quests can give
UENUM()
enum class EObjectiveTypes : uint8
{
	LOCATION,
	COLLECT,
	KILL
};



UCLASS()
class MYPROJECT_API AC_BaseQuest : public AActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	

	AC_BaseQuest();

	// Containers

	FObjectiveData ObjectiveData;

	// Variables

	FName QuestName;

	FName QuestDescription;

	FName TurnInText;

	bool bIsStoryQuest;

	bool bIsCompleted;

	UPROPERTY(EditInstanceOnly, Category = "Quests")
	AC_BaseQuest* PreRequisiteQuest;

	TArray<FObjectiveData> ObjectivesArray;


};
