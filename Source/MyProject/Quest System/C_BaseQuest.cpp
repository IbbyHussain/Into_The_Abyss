
#include "C_BaseQuest.h"
#include "MyProject/Quest System/C_LocationMarker.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/AI/C_BaseAI.h"

AC_BaseQuest::AC_BaseQuest()
{

}

void AC_BaseQuest::BeginPlay()
{
	Super::BeginPlay();

	CheckLocationObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckLocationObjective);
	CheckInteractionObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckInteractionObjective);
	CheckKilledEnemyObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckKilledEnemyObjective);
	CheckPuzzleObjectiveDelegate.AddDynamic(this, &AC_BaseQuest::CheckPuzzleObjective);
}

void AC_BaseQuest::OrganiseQuestInEditor()
{
	// SetLocation to whatever this actor is attached to
	SetActorLocation(GetAttachParentActor()->GetActorLocation());
}

void AC_BaseQuest::CheckLocationObjective(AC_LocationMarker* LocationReached)
{
	
	//UE_LOG(LogTemp, Warning, TEXT("CHECK LOCATION OBJECTIVE DELEGATE CALLED"));

	bool bUpdateUI;

	for (int i = 0; i < ObjectivesArray.Num(); i++)
	{
		int ObjectiveNumber = i;

		if ((!ObjectivesArray[i].bIsObjectiveComplete) && ObjectivesArray[i].ObjectiveTarget == LocationReached)
		{
			//UE_LOG(LogTemp, Warning, TEXT("COMPLETE"));
			ObjectivesArray[ObjectiveNumber].bIsObjectiveComplete = true;
			bUpdateUI = true;
		}
	}

	if (bUpdateUI)
	{
		// Update Objectives
		AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->UpdateObjectives();
	}
	
}

void AC_BaseQuest::CheckInteractionObjective(AActor* InteractionTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK interact OBJECTIVE DELEGATE CALLED"));

	
	bool bUpdateUI;

	for (int i = 0; i < ObjectivesArray.Num(); i++)
	{
		int ObjectiveNumber = i;

		if ((!ObjectivesArray[i].bIsObjectiveComplete) && ObjectivesArray[i].ObjectiveTarget == InteractionTarget)
		{
			UE_LOG(LogTemp, Warning, TEXT("INTERACTION COMPLETE"));
			ObjectivesArray[ObjectiveNumber].bIsObjectiveComplete = true;
			bUpdateUI = true;
		}
	}

	if (bUpdateUI)
	{
		// Update Objectives
		AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->UpdateObjectives();
	}
	
}

void AC_BaseQuest::CheckKilledEnemyObjective(AC_BaseAI* EnemyTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("CHECK kill OBJECTIVE DELEGATE CALLED"));

	
	bool bUpdateUI;

	for (int i = 0; i < ObjectivesArray.Num(); i++)
	{
		int ObjectiveNumber = i;

		if ((!ObjectivesArray[i].bIsObjectiveComplete) && ObjectivesArray[i].ObjectiveTarget->GetClass() == EnemyTarget->GetClass())
		{
			CurrentKillCount++;

			if (CurrentKillCount >= ObjectivesArray[i].ObjectiveNumber)
			{
				UE_LOG(LogTemp, Warning, TEXT("KILL COMPLETE"));
				ObjectivesArray[ObjectiveNumber].bIsObjectiveComplete = true;
				bUpdateUI = true;
			}
		}
	}

	if (bUpdateUI)
	{
		// Update Objectives
		AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->UpdateObjectives();
	}
	
}

void AC_BaseQuest::CheckPuzzleObjective(AActor* Puzzle)
{
	// Puzzle objectives can be completed before accepting the quest

	//UE_LOG(LogTemp, Warning, TEXT("CHECK puzzle OBJECTIVE DELEGATE CALLED"));

	bool bUpdateUI;

	for (int i = 0; i < ObjectivesArray.Num(); i++)
	{
		int ObjectiveNumber = i;

		if ((!ObjectivesArray[i].bIsObjectiveComplete) && ObjectivesArray[i].ObjectiveTarget == Puzzle)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Puzzle COMPLETE"));
			ObjectivesArray[ObjectiveNumber].bIsObjectiveComplete = true;
			bUpdateUI = true;
		}
	}

	if (bUpdateUI && bHasBeenAccepted)
	{
		// Update Objectives
		AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->UpdateObjectives();
	}
	
}

