
#include "C_SavingManager.h"
#include "MyProject/Misc/C_Checkpoint.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"

AC_SavingManager::AC_SavingManager()
{
	
}

void AC_SavingManager::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(PlayerCharacter)
	{
		PlayerCharacter->LockedAbilities(bIsDashLocked, bIsCrouchLocked, bIsSlideLocked, bIsWeaponWheelLocked);
	}

	FTimerHandle SpawnHandle;
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AC_SavingManager::CheckForSave, 1.0f, false);
}


void AC_SavingManager::CheckForSave()
{
	AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if(HUD)
	{
		HUD->HideLockedWidgets(bDisableMagicBar, bDisableHealthBar, bDisableSouls);
		HUD->UnlockWeaponWheelAbilities(bUnlockSword, bUnlockMagic, bUnlockCrossbow);
	}

	if(PlayerCharacter->GetCharacterMovement()->IsFalling())
	{
		PlayerCharacter->SetActorLocation(DefaultPlayerLocation);
		UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(DefaultPlayerRotation);
	}

}