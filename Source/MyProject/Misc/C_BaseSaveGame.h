// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "C_BaseSaveGame.generated.h"

UCLASS()
class MYPROJECT_API UC_BaseSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UC_BaseSaveGame();

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FVector PlayerLocation;

    // Crossbow bolts

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    int32 NumberOfSteelBolts;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    int32 NumberOfCopperBolts;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    int32 NumberOfCrystalBolts;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    int32 NumberOfFlareBolts;

    //Defaults

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    uint32 UserIndex;

    // Player

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    int32 Currency;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    FString CurrentLevel;

    // Key Bidnings

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    TArray<FString> KeyNameArray;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    FString SavedKey;

};
