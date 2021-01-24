// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "C_FlareBolt.generated.h"

UCLASS()
class MYPROJECT_API AC_FlareBolt : public AC_Crossbowbolt
{
	GENERATED_BODY()

	AC_FlareBolt();

private:
	virtual void SpawnHitEffect() override;

	// Returns a random X and Y co-ordinate in a cirlce
	TTuple<float, float> GetRandomPointInCircle();

	UPROPERTY(EditDefaultsOnly, Category = "Bolts")
	TArray<TSubclassOf<class AC_SteelBolt>> SteelBoltClassArray;

	UPROPERTY(EditDefaultsOnly, Category = "Bolts")
	TArray<class AC_SteelBolt*> SteelBoltArray;

	// The radius of the circle where random bolts will spawn within
	float Radius;

	FTimerHandle SpawnFlareBoltsHandle;

	void Fire();

	FTimerHandle DestroyComponentsHandle;

	void DestroyComponents();

	// The effect on the bolt mesh
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UParticleSystemComponent* BoltParticleComp;

	// Accessed in flare bolt so that it can be destroyed
	class AC_StaticMeshActor* FlareBoltAfterIndicator;

	UPROPERTY(EditDefaultsOnly, Category = "Crossbow")
	TSubclassOf<class AC_StaticMeshActor> FlareBoltAfterIndicatorClass;
};
