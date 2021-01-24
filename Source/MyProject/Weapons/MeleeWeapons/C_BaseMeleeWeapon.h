#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "C_BaseMeleeWeapon.generated.h"

UCLASS()
class MYPROJECT_API AC_BaseMeleeWeapon : public AC_StaticMeshActor
{
	GENERATED_BODY()

	AC_BaseMeleeWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage;

public:

	
};
