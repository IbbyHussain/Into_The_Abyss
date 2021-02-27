
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseQuest.generated.h"

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

	AC_BaseQuest();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	

	// Variables

	FName QuestName;

	FName QuestDescription;

	FName TurnInText;

	bool bIsStoryQuest;

	bool bIsCompleted;

	UPROPERTY(EditInstanceOnly, Category = "Quests")
	AC_BaseQuest* PreRequisiteQuest;


};
