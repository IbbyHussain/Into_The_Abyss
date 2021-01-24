// Fill out your copyright notice in the Description page of Project Settings.


#include "C_FlareBoltPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"

void AC_FlareBoltPickup::Interact_Implementation()
{
	OnInteractBasic();

	// If the number of current bolts is less than the max number of bolts then can add more bolts
	if (PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts < 
		PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->MaxAmountOfBolts)
	{
		if (PlayerCharacter->Crossbow.CurrentDummyBolt == PlayerCharacter->Crossbow.CrossbowObject->DummyBoltsArray[3])
		{
			if (PlayerCharacter->Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0 && PlayerCharacter->CombatState == ECombatState::RANGED)
			{
				PlayerCharacter->SpawnDummyBolt();
			}
		}

		// Increments and updates UI and saves value
		PlayerCharacter->UpdateNumberOfBolts(PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);

		if (PlayerCharacter->FlareBoltIndicator)
		{
			PlayerCharacter->FlareBoltIndicator->Destroy();
		}
		PlayerCharacter->ShouldSpawnFlareBoltIndicator();
		
	}
}
