// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MeleeAI.h"
#include "Engine/World.h"

AC_MeleeAI::AC_MeleeAI()
{
	PrimaryActorTick.bCanEverTick = true;

	// change when savage class is created
	TypeOfAI = ETypeOfAI::SAVAGE;

	bShouldTimerRun = false;
}

void AC_MeleeAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Melee AI is ticking"));

	StartMeleeTimer();
}

void AC_MeleeAI::BeginPlay()
{
	Super::BeginPlay();

	// Place holder time should start when the AI starts to wander around player character
	bShouldTimerRun = true;
}

void AC_MeleeAI::BasicAttack()
{
	// Plays a random attack animation
	int a = FMath::RandRange(0, 1);
	PlayAnimMontage(AttackMontageArray[a], 1.0f);
}

void AC_MeleeAI::StartMeleeTimer()
{
	if(bShouldTimerRun)
	{
		AITime = AITime + GetWorld()->GetDeltaSeconds();

		
		//UE_LOG(LogTemp, Warning, TEXT("started: %f"), AITime);
	}
	
	else
	{
		AITime = 0.0f;
		//UE_LOG(LogTemp, Warning, TEXT("stopped: %f"), AITime);
	}
}

void AC_MeleeAI::ResetMeleeTimer()
{
	if(bShouldTimerRun)
	{
		AITime = 0.0f;
	}
}