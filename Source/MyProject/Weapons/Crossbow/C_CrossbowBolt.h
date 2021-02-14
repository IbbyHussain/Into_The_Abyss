// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "C_Crossbowbolt.generated.h"

UCLASS()
class MYPROJECT_API AC_Crossbowbolt : public AC_StaticMeshActor
{
	GENERATED_BODY()

public:

	AC_Crossbowbolt();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	bool bIsPlayerBolt;

	// The amount of damage this actor will deal 
	float BoltDamage;

	// Number of bolts
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfBolts;

	int32 MaxAmountOfBolts;

	int32 Price;

	bool CanFire();

	// Dummy bolt associated with this class
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AC_DummyBolt> CorrespondingDummyBolt;

	// The impact effect that will be played
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UParticleSystem* BoltHitParticle;

	// The Sound effect that will be played
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	USoundBase* BoltHitSound;

	void SetGravity(float Gravity);

	void SetVelocity(float Velocity);

	float DefaultGravity;

	float DefaultVelocity;

protected:

	// Projectile movement component.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	virtual void SpawnHitEffect();

	UParticleSystemComponent* BoltHitParticleComp;

	bool bShouldStaggerAI;

private:

	// Sphere collision component.
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UBoxComponent* CollisionComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	// Overlap function for damage 
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bHasOverlapped;

	void StopBolt();
};
