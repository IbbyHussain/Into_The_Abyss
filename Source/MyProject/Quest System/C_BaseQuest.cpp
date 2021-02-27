
#include "C_BaseQuest.h"

AC_BaseQuest::AC_BaseQuest()
{

}

void AC_BaseQuest::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Quest Name is: %s"), *QuestName.ToString());

}

void AC_BaseQuest::OrganiseQuestInEditor()
{
	// SetLocation to whatever this actor is attached to
	SetActorLocation(GetAttachParentActor()->GetActorLocation());
}

void AC_BaseQuest::CheckLocationObjective()
{
}

void AC_BaseQuest::CheckInteractionObjective()
{
}

void AC_BaseQuest::CheckKilledEnemyObjective()
{
}


