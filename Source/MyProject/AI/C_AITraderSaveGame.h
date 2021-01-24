// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "C_AITraderSaveGame.generated.h"

UCLASS()
class MYPROJECT_API UC_AITraderSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UC_AITraderSaveGame();

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    int32 NumberOfFlareBolts;

    //Defaults

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;
};
