// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ArcherAI.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"

void AC_ArcherAI::ChangeAIColour()
{
	Super::ChangeAIColour();

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 0);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 1);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 2);
}

void AC_ArcherAI::BasicAttack()
{
	Super::BasicAttack();

	PlayAnimMontage(AttackMontage, 1.0f);
	// fire a projectile
}