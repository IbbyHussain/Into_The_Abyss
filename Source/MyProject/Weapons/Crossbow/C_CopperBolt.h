// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "C_CopperBolt.generated.h"

UCLASS()
class MYPROJECT_API AC_CopperBolt : public AC_Crossbowbolt
{
	GENERATED_BODY()

	AC_CopperBolt();

private:

	virtual void SpawnHitEffect() override;

	FTimerHandle BombletSpawnHandle;

	void SpawnBomblets();

	TArray<class AC_CopperBoltBomblet*> BombletArray;

	UPROPERTY(EditDefaultsOnly, Category = "Bomblets")
	TArray<TSubclassOf<AC_CopperBoltBomblet>> CopperBombletClassArray;

	void Launch();

	FTimerHandle LaunchHandle;

	AC_CopperBoltBomblet* a1;
	AC_CopperBoltBomblet* a2;
	AC_CopperBoltBomblet* a3;
	AC_CopperBoltBomblet* a4;

	virtual void BeginPlay() override;
};
