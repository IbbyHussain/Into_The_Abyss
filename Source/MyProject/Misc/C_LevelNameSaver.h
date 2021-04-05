// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_LevelNameSaver.generated.h"

UCLASS()
class MYPROJECT_API AC_LevelNameSaver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_LevelNameSaver();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void SaveCurrentLevel();

	UFUNCTION(BlueprintCallable)
	void LoadSavedLevel();

	UFUNCTION(BlueprintCallable)
	void ResetLevelName();

};
