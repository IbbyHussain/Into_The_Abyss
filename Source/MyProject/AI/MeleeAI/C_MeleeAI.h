
#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseCustomisedAI.h"
#include "C_MeleeAI.generated.h"

UCLASS()
class MYPROJECT_API AC_MeleeAI : public AC_BaseCustomisedAI
{
	GENERATED_BODY()

private:

	virtual void Tick(float DeltaTime) override;

	virtual void OnDeath() override;

protected:

	AC_MeleeAI();

	UPROPERTY(EditDefaultsOnly, Category = "Basic Attacks")
	TArray<UAnimMontage*> AttackMontageArray;

	virtual void BeginPlay() override;

public:

	//UPROPERTY(EditDefaultsOnly, Category = "Melee AI")
	//UAnimMontage* BasicAttackMontage;

	UPROPERTY(EditInstanceOnly, Category = "Melee AI")
	class AC_AIFightManager* FightManager;

	void BasicAttack();

	void MeleeAIDamage(USkeletalMeshComponent* SKMesh, float Damage);

	FName WeaponHiltSocket;

	FName WeaponTipSocket;

	void StartMeleeTimer();

	UFUNCTION(BlueprintCallable)
	void ResetMeleeTimer();

	bool bShouldTimerRun;

	float AITime;

	bool bCanAttack;
};
