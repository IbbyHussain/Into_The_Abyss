// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CopperBoltPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"

AC_CopperBoltPickup::AC_CopperBoltPickup()
{

}

void AC_CopperBoltPickup::Interact_Implementation()
{
	OnInteractBasic();

	// If the value of Souls goes over its max value, set it back to it's max value.
	if (PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[1]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts < 
		PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[1]->GetDefaultObject<AC_Crossbowbolt>()->MaxAmountOfBolts)
	{
		if (PlayerCharacter->Crossbow.CurrentDummyBolt == PlayerCharacter->Crossbow.CrossbowObject->DummyBoltsArray[1])
		{
			if (PlayerCharacter->Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0 && PlayerCharacter->CombatState == ECombatState::RANGED)
			{
				PlayerCharacter->SpawnDummyBolt();
			}
		}
		// Increments and updates UI and saves value
		PlayerCharacter->UpdateNumberOfBolts(PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[1]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);
	}
}
