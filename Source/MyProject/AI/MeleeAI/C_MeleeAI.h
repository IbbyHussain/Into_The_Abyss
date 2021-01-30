
#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseCustomisedAI.h"
#include "C_MeleeAI.generated.h"

UCLASS()
class MYPROJECT_API AC_MeleeAI : public AC_BaseCustomisedAI
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	AC_MeleeAI();

	UPROPERTY(EditDefaultsOnly, Category = "Basic Attacks")
	TArray<UAnimMontage*> AttackMontageArray;

public:

	//UPROPERTY(EditDefaultsOnly, Category = "Melee AI")
	//UAnimMontage* BasicAttackMontage;

	void BasicAttack();

	void StartMeleeTimer();

	UFUNCTION(BlueprintCallable)
	void ResetMeleeTimer();

	bool bShouldTimerRun;

	float AITime;
};
