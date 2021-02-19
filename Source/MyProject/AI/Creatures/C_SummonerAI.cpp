// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SummonerAI.h"
#include "Kismet/GameplayStatics.h"

AC_SummonerAI::AC_SummonerAI()
{

}

void AC_SummonerAI::OnDeath()
{
	Super::OnDeath();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
	// spawn particle effect
}

void AC_SummonerAI::TeleportToLocationEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), TeleportSound, GetActorLocation());
}
