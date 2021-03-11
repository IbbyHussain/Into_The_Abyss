// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ReactorBeam.generated.h"

UCLASS()
class MYPROJECT_API AC_ReactorBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_ReactorBeam();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Beam")
	class UNiagaraComponent* BeamComp;

	// Exposed Variables

	// The location of where the beam will strike, used when beam uses random points 
	UPROPERTY(EditAnywhere, Category = "Beam")
	FVector BeamTargetLocation;

	// The max area the beam can hit
	UPROPERTY(EditAnywhere, Category = "Beam")
	float MaxBeamRange;

	// The min area the beam can hit
	UPROPERTY(EditAnywhere, Category = "Beam")
	float MinBeamRange;

	// The time it takes the lightning to hit a new target location
	UPROPERTY(EditAnywhere, Category = "Beam")
	float LightningFrequency;

	FTimerHandle ChangeTargetLocationHandle;

	// The location of the end of the beam
	UPROPERTY(EditAnywhere, Category = "Beam")
	AActor* EndActor;

	// The location of the tangents
	UPROPERTY(EditAnywhere, Category = "Beam")
	AActor* TangentActor;

	// Beam spawn

	void SpawnEffects();

	// The particle effect that will spawn when this actor spawns
	UPROPERTY(EditAnywhere, Category = "Beam")
	class UNiagaraSystem* SparksEffect;

	// beam corrupted

	void BeginCorruption();

	void BecomeCorrupted();

	bool bIsCorrupted;
};
