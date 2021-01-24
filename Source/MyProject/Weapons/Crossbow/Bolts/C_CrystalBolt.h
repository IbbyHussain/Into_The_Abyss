// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "C_CrystalBolt.generated.h"


UCLASS()
class MYPROJECT_API AC_CrystalBolt : public AC_Crossbowbolt
{
	GENERATED_BODY()

	AC_CrystalBolt();

private:

	virtual void SpawnHitEffect() override;

	virtual void BeginPlay() override;
	
};
