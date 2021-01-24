#include "C_SteelBolt.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AC_SteelBolt::AC_SteelBolt()
{
	

	BoltDamage = 0.1f;

	NumberOfBolts = 20;

	MaxAmountOfBolts = 20;

	Price = 1;

	DefaultGravity = 0.05f;
	DefaultVelocity = 2000.0f;

	ProjectileMovementComponent->InitialSpeed = DefaultVelocity;
	ProjectileMovementComponent->MaxSpeed = DefaultVelocity;
	ProjectileMovementComponent->ProjectileGravityScale = DefaultGravity;

	bShouldStaggerAI = true;
}

void AC_SteelBolt::SpawnHitEffect()
{
	Super::SpawnHitEffect();

	UE_LOG(LogTemp, Error, TEXT("STEEL bolt hit"));
}

void AC_SteelBolt::BeginPlay()
{
	Super::BeginPlay();

	// Allows the damage to be set in the editor
	BoltDamage = Damage;

	SetLifeSpan(5.0f);
}