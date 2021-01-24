#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_IceSpike.generated.h"

class UProjectileMovementComponent;

UCLASS()
class MYPROJECT_API AC_IceSpike : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_IceSpike();

	void Fire();

	void StopFire();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "cpp")
	class UProjectileMovementComponent* MovementComp;

protected:
	virtual void BeginPlay() override;

private:

	//UPROPERTY(EditDefaultsOnly, Category = "cpp")
	//USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category = "cpp")
	class UBoxComponent* BoxComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "cpp")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHit(const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "cpp")
	UParticleSystemComponent* TrailEffect;

	UParticleSystemComponent* DestroyEffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "cpp")
	UParticleSystem* DestroyEffect;

	UPROPERTY(EditDefaultsOnly, Category = "cpp")
	USoundBase* SummonSound;

	UPROPERTY(EditDefaultsOnly, Category = "cpp")
	USoundBase* DestroyedSound;

	FTimerHandle ExplosionEffectHandle;

	void DestroyActor();

	void SpawnDestroyedEffect();

	class AC_BaseAI* BaseAI;
};
