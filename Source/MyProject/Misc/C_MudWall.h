// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "C_MudWall.generated.h"


UCLASS()
class MYPROJECT_API AC_MudWall : public AC_StaticMeshActor
{
	GENERATED_BODY()

public:

	AC_MudWall();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Health")
	class UC_HealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	class UDestructibleComponent* DestructibleMeshComp;

	UFUNCTION()
	void UpdateHealth(UC_HealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser);

	//Damage States

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	UStaticMesh* State75;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	UStaticMesh* State50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	UStaticMesh* State25;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	USoundBase* DestroyedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	USoundBase* SummonedSound;

	void PlaySummonedSound();

	void DestroyWall();

	bool bHasDied;

	// Particles

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* SummonEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* DeSummonEffect;

	void PlaySummonEffect();

	void PlayDeSummonEffect();

	void DespawnSummonEffect();

	class UParticleSystemComponent* SummonEffectComponent;

	//TimeLine

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FWallCurve;

	// The timeline component
	UTimelineComponent* WallTimeline;

	// delegates for the timeline (update)
	FOnTimelineFloat WallInterpFunction{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void WallTimelineFloatReturn(float Value);

	void PlayWallAnim();

	FVector StartLocation;

	FVector EndLocation;

};
