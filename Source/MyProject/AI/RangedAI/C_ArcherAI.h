// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "C_ArcherAI.generated.h"

UCLASS()
class MYPROJECT_API AC_ArcherAI : public AC_MeleeAI
{
	GENERATED_BODY()

private:

	virtual void ChangeAIColour() override;

	virtual void BasicAttack() override;

	virtual void BeginPlay() override;

	class AC_Crossbow* Crossbow;

	UPROPERTY(EditDefaultsOnly, Category = "Archer Crossbow")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Archer Crossbow")
	TSubclassOf<class AC_DummyBolt> SteelDummyBolt;

	UPROPERTY(EditDefaultsOnly, Category = "Archer Crossbow")
	UAnimationAsset* CrossbowReloadMontage;
};
