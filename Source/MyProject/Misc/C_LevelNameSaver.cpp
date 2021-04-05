// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LevelNameSaver.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Misc/C_BaseSaveGame.h"

// Sets default values
AC_LevelNameSaver::AC_LevelNameSaver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_LevelNameSaver::BeginPlay()
{
	Super::BeginPlay();
}

void AC_LevelNameSaver::SaveCurrentLevel()
{
	FString a = UGameplayStatics::GetCurrentLevelName(this, true);
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		SaveGameInstance->CurrentLevel = UGameplayStatics::GetCurrentLevelName(this, true);

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("LevelSave"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Succeeded (LevelName), NOT IN MAIN MENU || Level name is %s"), *SaveGameInstance->CurrentLevel);
		}
	}
}

void AC_LevelNameSaver::LoadSavedLevel()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LevelSave"), 0)))
	{
		FName Level = *LoadedGame->CurrentLevel;
		UGameplayStatics::OpenLevel(this, Level);
		UE_LOG(LogTemp, Warning, TEXT("LEVEL NAME VALID || Level name is %s (LOADEDGAME) || And is %s (ASSIGNED FNAME)"), *LoadedGame->CurrentLevel, *Level.ToString());
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO SAVE SLOT FOUND"));
		UGameplayStatics::OpenLevel(this, FName("Level2-Part1"));
	}
}

void AC_LevelNameSaver::ResetLevelName()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		SaveGameInstance->CurrentLevel = ("Level2-Part1");

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("LevelSave"), 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Succeeded (LevelName) - RESET"));
		}
	}
}

