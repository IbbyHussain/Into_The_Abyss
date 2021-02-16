// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LostAdventurer.h"

AC_LostAdventurer::AC_LostAdventurer()
{

}

void AC_LostAdventurer::ChangeAIColour()
{
	Super::ChangeAIColour();

	UE_LOG(LogTemp, Error, TEXT("Lost adventurer change colours tyes"));

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 1);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 0);
}