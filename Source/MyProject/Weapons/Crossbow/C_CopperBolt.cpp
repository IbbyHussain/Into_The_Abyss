// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CopperBolt.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/C_BaseAI.h"

#include "MyProject/MyProject.h"

#include "MyProject/AI/C_BaseAI.h"
#include "EngineUtils.h"
#include "Particles/ParticleSystem.h"

#include "MyProject/Weapons/Crossbow/Bolts/C_CopperBoltBomblet.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AC_CopperBolt::AC_CopperBolt()
{
	BoltDamage = 0.05;

	NumberOfBolts = 15;

	MaxAmountOfBolts = 15;

	Price = 3;

	DefaultGravity = 0.65;
	DefaultVelocity = 1750.0f;

	ProjectileMovementComponent->InitialSpeed = DefaultVelocity;
	ProjectileMovementComponent->MaxSpeed = DefaultVelocity;
	ProjectileMovementComponent->ProjectileGravityScale = DefaultGravity;

	BombletArray = {};

	bShouldStaggerAI = true;
}

void AC_CopperBolt::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(5.0f);
}

void AC_CopperBolt::SpawnHitEffect()
{
	Super::SpawnHitEffect();

	FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredComponent();

	TArray<FHitResult> OutHits;

	FVector ActorLocation = GetActorLocation();

	// Creates a sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(200.0f);

	// Debug 
	//DrawDebugSphere(GetWorld(), ActorLocation, MyColSphere.GetSphereRadius(), 20, FColor::Red, true);

	// A sweep trace that will hit anything within the sphere
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, COLLISION_COPPERBOLTDETECTION, MyColSphere, CollisionParams);

	TArray<AC_BaseAI*> AIs;
	
	if(bHit)
	{
		for (auto& Hit : OutHits)
		{
			AC_BaseAI* AI = Cast<AC_BaseAI>(Hit.Actor);

			if(Hit.GetActor() == AI)
			{
				if (AI->bIsBoss)
				{
					UGameplayStatics::ApplyDamage(AI, 0.35f * AI->BossDamageReduction, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
				}
				else
				{
					UGameplayStatics::ApplyDamage(AI, 0.35f, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
				}
				
				AI->CheckForAIDeath();
			}
		}
	}

	GetWorldTimerManager().SetTimer(BombletSpawnHandle, this, &AC_CopperBolt::SpawnBomblets, 1.0f, false);
}

void AC_CopperBolt::SpawnBomblets()
{

	SetActorHiddenInGame(true);

	// Transform and spawn parameters of bomblets
	FActorSpawnParameters SpawnParams;
	FTransform Transform = GetActorTransform();
	FVector ActorLoc = Transform.GetLocation();
	FRotator ActorRot = Transform.GetRotation().Rotator();

	/*for (auto i : CopperBombletClassArray)
	{
		for(auto x :BombletArray)
		{
			x = GetWorld()->SpawnActor<AC_CopperBoltBomblet>(i, ActorLoc, ActorRot, SpawnParams);
		}
	}*/

	// Spawn bomblets individually, so that we can chnage rotation of each one
	a1 = GetWorld()->SpawnActor<AC_CopperBoltBomblet>(CopperBombletClassArray[0], ActorLoc, FRotator::ZeroRotator, SpawnParams);
	a2 = GetWorld()->SpawnActor<AC_CopperBoltBomblet>(CopperBombletClassArray[1], ActorLoc, FRotator::ZeroRotator, SpawnParams);
	a3 = GetWorld()->SpawnActor<AC_CopperBoltBomblet>(CopperBombletClassArray[2], ActorLoc, FRotator::ZeroRotator, SpawnParams);
	a4 = GetWorld()->SpawnActor<AC_CopperBoltBomblet>(CopperBombletClassArray[3], ActorLoc, FRotator::ZeroRotator, SpawnParams);

	// Set the rotation of bomblets, allows them to launch in different directions
	a1->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	a2->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
	a3->SetActorRotation(FRotator(0.0f, -180.0f, 0.0f));
	a4->SetActorRotation(FRotator(0.0f, -270.0f, 0.0f));

	// Add bomblet to array
	BombletArray = {a1, a2, a3, a4};

	GetWorldTimerManager().SetTimer(LaunchHandle, this, &AC_CopperBolt::Launch, 1.0f);
}

// Launches all bomblets
void AC_CopperBolt::Launch()
{
	for (auto x : BombletArray)
	{
		x->Launch();
	}
}