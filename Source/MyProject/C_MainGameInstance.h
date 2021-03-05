// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_MainGameInstance.generated.h"

UCLASS()
class MYPROJECT_API UC_MainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	int32 HealthQuantity;

	UPROPERTY(EditDefaultsOnly)
	int32 StaminaQuantity;

	UPROPERTY(EditDefaultsOnly)
	int32 ManaQuantity;

	UPROPERTY(EditDefaultsOnly)
	TArray<int32> QuantityArray;

	virtual void Init() override;

	
};
