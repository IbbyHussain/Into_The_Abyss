// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CrystalBolt.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/MyProject.h"

#include "Components/BoxComponent.h"

AC_CrystalBolt::AC_CrystalBolt()
{
	BoltDamage = 0.15;

	NumberOfBolts = 10;

	MaxAmountOfBolts = 10;

	Price = 5;

	DefaultGravity = 0.1f;
	DefaultVelocity = 2000.0f;

	ProjectileMovementComponent->InitialSpeed = DefaultVelocity;
	ProjectileMovementComponent->MaxSpeed = DefaultVelocity;
	ProjectileMovementComponent->ProjectileGravityScale = DefaultGravity;
}

void AC_CrystalBolt::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(5.0f);
}

void AC_CrystalBolt::SpawnHitEffect()
{
	Super::SpawnHitEffect();

	FCollisionQueryParams CollisionParams;

	TArray<FHitResult> OutHits;

	FVector ActorLocation = GetActorLocation();

	// Creates a sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(200.0f);

	// Debug sphere
	//DrawDebugSphere(GetWorld(), ActorLocation, MyColSphere.GetSphereRadius(), 20, FColor::Silver, true);

	// A sweep trace that will return anything hit within the sphere
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, COLLISION_COPPERBOLTDETECTION, MyColSphere, CollisionParams); 

	TArray<AC_BaseAI*> AIs;

	if (bHit)
	{
		for (auto& Hit : OutHits)
		{
			AC_BaseAI* AI = Cast<AC_BaseAI>(Hit.Actor);

			UE_LOG(LogTemp, Error, TEXT("Bomblet Hit: %s"), *Hit.GetActor()->GetName());

			// If an AI is within the sphere
			if (Hit.GetActor() == AI)
			{
				AI->BecomeBlind(AI->BlindAnimation, 6.0f);
			}
		}
	}
}