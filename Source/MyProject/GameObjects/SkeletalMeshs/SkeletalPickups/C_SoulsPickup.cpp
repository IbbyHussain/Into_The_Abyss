
#include "C_SoulsPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

AC_SoulsPickup::AC_SoulsPickup()
{

}

void AC_SoulsPickup::Interact_Implementation()
{
	OnInteractBasic();

	
	// If the value of Souls goes over its max value, set it back to it's max value.
	if (PlayerCharacter->NumberOfSouls < 30.0f)
	{
		//PlayerCharacter->NumberOfSouls = 30.0f;

		// Increments and Sends a signal to HUD widget to update text
		PlayerCharacter->NumberOfSouls++;
		PlayerCharacter->UpdatenumberOfSouls.Broadcast(PlayerCharacter->NumberOfSouls);
		
		// Saves the value
		PlayerCharacter->SaveNumberOfSouls();
	}
}
