
#include "C_ManaPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

AC_ManaPickup::AC_ManaPickup()
{

}

void AC_ManaPickup::Interact_Implementation()
{
	OnInteract(PlayerCharacter->Magic, 10.0f);

	if (PlayerHUD)
	{
		PlayerHUD->DisplayManaImage();
	}

	// If the value of magic goes over its max value, set it back to it's max value.
	if (PlayerCharacter->Magic > 100.0f)
	{
		PlayerCharacter->Magic = 100.0f;
	}
}

