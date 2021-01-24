
#include "C_HealthPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

AC_HealthPickup::AC_HealthPickup()
{

}

void AC_HealthPickup::Interact_Implementation()
{
	// If the player character is not at max health 
	//if (!(PlayerCharacter->Health >= 100.0f))
	
	OnInteract(PlayerCharacter->Health, 10.0f);

	// Temporary solution
	if (PlayerHUD)
	{
		PlayerHUD->DisplayHealthImage();
	}

	// If the value of health goes over its max value, set it back to it's max value.
	if (PlayerCharacter->Health > 100.0f)
	{
		PlayerCharacter->Health = 100.0f;
	}
}
