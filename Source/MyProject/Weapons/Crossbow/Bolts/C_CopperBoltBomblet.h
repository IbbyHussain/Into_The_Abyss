// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/StaticMeshs/C_StaticMeshActorPhysics.h"
#include "C_CopperBoltBomblet.generated.h"

UCLASS()
class MYPROJECT_API AC_CopperBoltBomblet : public AC_StaticMeshActorPhysics
{
	GENERATED_BODY()

private:
	AC_CopperBoltBomblet();

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Launch();

	void Explode();

	// The impact effect that will be played
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UParticleSystem* BombletExplodeParticle;

	// The sound effect that will be played
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	USoundBase* BombletExplodeSound;

	// Handle used to explode the bomblet
	FTimerHandle ExplodeHandle;

	// Timer used to pulse 
	FTimerHandle PulseHandle;

	void Pulse();

	// Dynamic material for pulse 
	UMaterialInstanceDynamic* MatInst;


};
