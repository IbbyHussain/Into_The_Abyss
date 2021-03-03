
#include "C_BaseQuest.h"

AC_BaseQuest::AC_BaseQuest()
{

}

void AC_BaseQuest::BeginPlay()
{
	Super::BeginPlay();

	CheckLocationObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckLocationObjective);
	CheckInteractionObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckInteractionObjective);
	CheckKilledEnemyObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckKilledEnemyObjective);
}

void AC_BaseQuest::OrganiseQuestInEditor()
{
	// SetLocation to whatever this actor is attached to
	SetActorLocation(GetAttachParentActor()->GetActorLocation());
}

void AC_BaseQuest::CheckLocationObjective()
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK LOCATION OBJECTIVE DELEGATE CALLED"));
}

void AC_BaseQuest::CheckInteractionObjective()
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK interact OBJECTIVE DELEGATE CALLED"));
}

void AC_BaseQuest::CheckKilledEnemyObjective()
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK kill OBJECTIVE DELEGATE CALLED"));
}


