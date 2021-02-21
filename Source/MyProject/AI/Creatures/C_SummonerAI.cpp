// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SummonerAI.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/Creatures/C_SummonerProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyProject/AI/Creatures/C_RollerAI.h"

AC_SummonerAI::AC_SummonerAI()
{

}

void AC_SummonerAI::OnDeath()
{
	Super::OnDeath();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
}

void AC_SummonerAI::SummonerBasicAttack()
{
	// play sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	
	// play anim
	PlayAnimMontage(AttackMontage, 1.0f);

	// Spawn projectile 
	FActorSpawnParameters SpawnParams;

	FTransform ProjectileTransform = GetMesh()->GetSocketTransform(("ProjectileSocket"), ERelativeTransformSpace::RTS_World);
	FVector ProjectileSpawnLocation = ProjectileTransform.GetLocation();
	FRotator ProjectileSpawnRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnLocation, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());

	AC_SummonerProjectile* Projectile = GetWorld()->SpawnActor<AC_SummonerProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation, SpawnParams);
}

void AC_SummonerAI::SummonerSpecialAttack()
{
	FActorSpawnParameters SpawnParams;

	FTransform Roller1Transform = GetMesh()->GetSocketTransform(("Roller1"), ERelativeTransformSpace::RTS_World);
	FVector Roller1SpawnLocation = Roller1Transform.GetLocation();

	AC_RollerAI* RollerAI1 = GetWorld()->SpawnActor<AC_RollerAI>(RollerAIClass, Roller1SpawnLocation, FRotator::ZeroRotator, SpawnParams);

	FTransform Roller2Transform = GetMesh()->GetSocketTransform(("Roller2"), ERelativeTransformSpace::RTS_World);
	FVector Roller2SpawnLocation = Roller2Transform.GetLocation();

	AC_RollerAI* RollerAI2 = GetWorld()->SpawnActor<AC_RollerAI>(RollerAIClass, Roller2SpawnLocation, FRotator::ZeroRotator, SpawnParams);
}


void AC_SummonerAI::TeleportToLocationEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), TeleportSound, GetActorLocation());
}

