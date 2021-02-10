// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MeleeAI.h"
#include "Engine/World.h"
#include "MyProject/Weapons/MeleeWeapons/C_BaseSkeletalMeleeWeapon.h"
#include "MyProject/MyProject.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/AI/C_AIFightManager.h"


AC_MeleeAI::AC_MeleeAI()
{
	PrimaryActorTick.bCanEverTick = true;

	// change when savage class is created
	TypeOfAI = ETypeOfAI::SAVAGE;

	bShouldTimerRun = false;

	WeaponHiltSocket = ("WeaponHiltSocket");

	WeaponTipSocket = ("WeaponTipSocket");

	bCanAttack = true;
}

void AC_MeleeAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AC_MeleeAI::MeleeAIDamage(USkeletalMeshComponent* SKMesh, float Damage)
{
	AC_BaseSkeletalMeleeWeapon* WeaponPTR = Cast<AC_BaseSkeletalMeleeWeapon>(Weapon);

	if(WeaponPTR)
	{
		//UE_LOG(LogTemp, Warning, TEXT("WEAPON PTR WAS VALID"));

		// Get the start and end location of the sphere trace (two sockets that are the length of the sword)
		FVector StartLocation = WeaponPTR->MeshComp->GetSocketLocation(WeaponTipSocket); // make mesh in skeletal mesh paraent public then get socket location.
		FVector EndLocation = WeaponPTR->MeshComp->GetSocketLocation(WeaponHiltSocket);

		FHitResult HitResult;

		TArray<AActor*> ActorsIgnored;
		ActorsIgnored = { this };

		// Convert the collision type to standard collision channel
		ETraceTypeQuery Trace6 = UEngineTypes::ConvertToTraceType(ECollisionChannel::COLLISION_AIMELEEDETECTION);

		bool bHits = UKismetSystemLibrary::SphereTraceSingle(SKMesh, StartLocation, EndLocation, 25.0f, Trace6, false, ActorsIgnored, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green);

		AC_PlayerCharacter* PlayerCharacterPTR = Cast<AC_PlayerCharacter>(HitResult.GetActor());

		if (bHits && PlayerCharacterPTR && bCanAttack)
		{
			//UE_LOG(LogTemp, Error, TEXT("Hit player"))
			PlayerCharacterPTR->ApplyDamageToPlayer(Damage);
			bCanAttack = false;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("WEAPON PTR WAS not VALID"));
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

void AC_MeleeAI::OnDeath()
{
	Super::OnDeath();

	FightManager->DestroyManager();
}