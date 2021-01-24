

#include "C_SteelBoltPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"

AC_SteelBoltPickup::AC_SteelBoltPickup()
{

}

void AC_SteelBoltPickup::Interact_Implementation()
{
	// if player character combat state is ranged then: 
	OnInteractBasic();

	// If the value of Souls goes over its max value, set it back to it's max value.
	if (PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts < 
		PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->MaxAmountOfBolts)
	{
		if (PlayerCharacter->Crossbow.CurrentDummyBolt == PlayerCharacter->Crossbow.CrossbowObject->DummyBoltsArray[0])
		{
			if (PlayerCharacter->Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0 && PlayerCharacter->CombatState == ECombatState::RANGED)
			{
				PlayerCharacter->SpawnDummyBolt();
			}
		}

		// Increments and updates UI and saves value
		PlayerCharacter->UpdateNumberOfBolts(PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);
	}
}