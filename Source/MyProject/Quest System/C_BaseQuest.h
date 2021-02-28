
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseQuest.generated.h"

UENUM()
namespace EObjectiveTypes {
	enum Type {
		LOCATION UMETA(DisplayName = "Location"),
		INTERACT UMETA(DisplayName = "Interact"),
		KILL UMETA(DisplayName = "Kill")
	};
}

USTRUCT(BlueprintType)
struct FObjectiveData
{
	GENERATED_BODY() 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	bool bIsObjectiveComplete;

	// Which enemy type to kill
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	AActor* ObjectiveTarget;

	// e.g number of targets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	int32 ObjectiveNumber;

public:
	//UPROPERTY(EditAnywhere, Category = "Struct")
	//EObjectiveTypes ObjectiveTypes;

	UPROPERTY(EditAnywhere, Category = "Struct")
	TEnumAsByte<EObjectiveTypes::Type> ObjectiveTypes;

	FObjectiveData()
	{

	}

};

UCLASS()
class MYPROJECT_API AC_BaseQuest : public AActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:	

	AC_BaseQuest();

	// Containers

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	FObjectiveData ObjectiveData;

	// Variables

	// FText so that it works with widgets

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	FText TurnInText;

	//bool bIsStoryQuest;

	bool bIsCompleted;

	UPROPERTY(EditInstanceOnly, Category = "Quests")
	AC_BaseQuest* PreRequisiteQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	TArray<FObjectiveData> ObjectivesArray;

	// functions

	UFUNCTION(BlueprintCallable, CallInEditor)
	void OrganiseQuestInEditor();

	void CheckLocationObjective();

	void CheckInteractionObjective();

	void CheckKilledEnemyObjective();

};
