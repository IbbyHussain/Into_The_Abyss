// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PeasantAI.h"

AC_PeasantAI::AC_PeasantAI()
{

}

void AC_PeasantAI::ChangeAIColour()
{
	Super::ChangeAIColour();

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 0);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 1);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 2);
}