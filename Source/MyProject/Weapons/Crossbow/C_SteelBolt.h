// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "C_SteelBolt.generated.h"


UCLASS()
class MYPROJECT_API AC_SteelBolt : public AC_Crossbowbolt
{
	GENERATED_BODY()

private:

	virtual void SpawnHitEffect() override;

public:

	AC_SteelBolt();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "DMG")
	float Damage;
	
};
