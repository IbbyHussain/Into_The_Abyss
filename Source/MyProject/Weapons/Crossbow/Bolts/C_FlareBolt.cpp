// Fill out your copyright notice in the Description page of Project Settings.


#include "C_FlareBolt.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Weapons/Crossbow/C_SteelBolt.h"

#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SkeletalPickupBase.h"
#include "Particles/ParticleSystemComponent.h"

#include "MyProject/C_PlayerCharacter.h"

AC_FlareBolt::AC_FlareBolt()
{
	BoltDamage = 0.25;

	NumberOfBolts = 5;

	MaxAmountOfBolts = 5;

	Price = 10;

	DefaultGravity = 0.0f;
	DefaultVelocity = 2000.0f;

	ProjectileMovementComponent->InitialSpeed = DefaultVelocity;
	ProjectileMovementComponent->MaxSpeed = DefaultVelocity;
	ProjectileMovementComponent->ProjectileGravityScale = DefaultGravity;

	BoltParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bolt Particle Comp"));
	BoltParticleComp->SetupAttachment(RootComponent);
	BoltParticleComp->SetRelativeLocation(FVector(24.0f, 0.0f, 0.0f));

	Radius = 200.0f;

	bShouldStaggerAI = true;
}


void AC_FlareBolt::SpawnHitEffect()
{
	Super::SpawnHitEffect();

	GetWorldTimerManager().SetTimer(SpawnFlareBoltsHandle, this, &AC_FlareBolt::Fire, 3.0f, false);

	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(PlayerCharacter->FlareBoltIndicator->IsHidden() == false)
	{
		FActorSpawnParameters SpawnParams;
		FlareBoltAfterIndicator = GetWorld()->SpawnActor<AC_StaticMeshActor>(FlareBoltAfterIndicatorClass, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 4.0f), FRotator::ZeroRotator, SpawnParams);
	}
}

// This is a non-uniform method(Points are more concentrated in the centre)
TTuple<float, float> AC_FlareBolt::GetRandomPointInCircle()
{
	// Centre of the circle
	float CentreCircleX = GetActorLocation().X;
	float CentreCircleY = GetActorLocation().Y;

	// Generate a random float from 0 to 1
	float RandomNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

	// Produces random angle, in degrees
	float Theeta = 2 * 360.0f * RandomNum;

	// Produces random radius
	float RandomRadius = Radius * UKismetMathLibrary::Sqrt(RandomNum);

	//Random x and y Co-ordinates, within circle or on circumference
	float RandomXc = RandomRadius * UKismetMathLibrary::Cos(Theeta) + CentreCircleX;
	float RandomYc = RandomRadius * UKismetMathLibrary::Sin(Theeta) + CentreCircleY;

	// returns the random x and y co-ordinates
	return MakeTuple(RandomXc, RandomYc);
}

void AC_FlareBolt::Fire()
{
	FTransform FlareBoltTransform = GetActorTransform();

	//Ensures the circle is perpendicular to the ground
	FlareBoltTransform.SetRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Draws a cirlce
	//DrawDebugCircle(GetWorld(), FlareBoltTransform.ToMatrixNoScale(), Radius, 50, FColor::Orange, true, -1.0f);

	FActorSpawnParameters SpawnParams;

	// Steel Bolts will launch towards the ground
	FRotator SteelBoltRotation = FRotator(-90.0f, 0.0f, 0.0f);

	for (auto i : SteelBoltClassArray)
	{
		for (auto x : SteelBoltArray)
		{
			// Gets a random x and y co-ordinate from the circle
			TTuple <float, float> RandomPoint = GetRandomPointInCircle();

			// Spawns a steel Bolt at a random location
			x = GetWorld()->SpawnActor<AC_SteelBolt>(i, FVector(RandomPoint.Get<0>(), RandomPoint.Get<1>(), GetActorLocation().Z + 1500.0f), SteelBoltRotation, SpawnParams);
		}
	}
	
	GetWorldTimerManager().ClearTimer(SpawnFlareBoltsHandle);
	GetWorldTimerManager().SetTimer(DestroyComponentsHandle, this, &AC_FlareBolt::DestroyComponents, 0.75f, false);
}

void AC_FlareBolt::DestroyComponents()
{
	// Removes the particle effect, the AfterIndicator is destroyed in its BP
	if(BoltHitParticleComp)
	{
		BoltHitParticleComp->DestroyComponent();
	}
	Destroy();
}
