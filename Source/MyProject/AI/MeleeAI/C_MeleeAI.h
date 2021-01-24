
#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseCustomisedAI.h"
#include "C_MeleeAI.generated.h"

UCLASS()
class MYPROJECT_API AC_MeleeAI : public AC_BaseCustomisedAI
{
	GENERATED_BODY()

	AC_MeleeAI();

private:

	virtual void BeginPlay() override;

protected:

public:

	UPROPERTY(EditDefaultsOnly, Category = "Melee AI")
	UAnimMontage* BasicAttackMontage;

	void BasicAttack();

	
};
