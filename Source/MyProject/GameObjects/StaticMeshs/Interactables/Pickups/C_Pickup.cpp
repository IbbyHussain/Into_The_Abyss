
#include "C_Pickup.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "TimerManager.h"

AC_Pickup::AC_Pickup()
{
	Attachpoint = ("");
}


void AC_Pickup::OnInteract(float Stat, float Amount)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation(), 1.0f);

	float total = Stat += Amount;

	UParticleSystemComponent* DespawnComponent = UGameplayStatics::SpawnEmitterAttached(DespawnEffect, MeshComp, 
		Attachpoint, GetActorLocation(), GetActorRotation(), EAttachLocation::SnapToTarget);

	GetWorldTimerManager().SetTimer(DespawnHandle, this, &AC_Pickup::DestroyThis, 1.5f, false);

}

void AC_Pickup::DestroyThis()
{
	Destroy();
}

void AC_Pickup::Interact_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("C_Pickup: Interacted with a STATIC MESH Pickup "));
}
