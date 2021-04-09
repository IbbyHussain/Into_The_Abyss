// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"

UC_BaseSaveGame::UC_BaseSaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;

	KeyNameArray.SetNum(21);
	KeyNameArray[0] = "E";
	//KeyNameArray.Init(("Key"), 21);
}
