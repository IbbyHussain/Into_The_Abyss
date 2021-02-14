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

	UPROPERTY(EditDefaultsOnly, Category = "Basic Attacks")
	UAnimMontage* AttackMontage;
};
