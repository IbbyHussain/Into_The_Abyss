
#include "C_StaminaPickup.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

AC_StaminaPickup::AC_StaminaPickup()
{

}

void AC_StaminaPickup::Interact_Implementation()
{
	OnInteract(PlayerCharacter->Stamina, 10.0f);

	if (PlayerHUD)
	{
		PlayerHUD->DisplayStaminaImage();
	}

	// If the value of health goes over its max value, set it back to it's max value.
	if (PlayerCharacter->Stamina > 100.0f)
	{
		PlayerCharacter->Stamina = 100.0f;
	}
}