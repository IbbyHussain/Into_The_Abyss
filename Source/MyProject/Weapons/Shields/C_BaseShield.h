#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "C_BaseShield.generated.h"

UCLASS()
class MYPROJECT_API AC_BaseShield : public AC_StaticMeshActor
{
	GENERATED_BODY()

	AC_BaseShield();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	float BlockAmount;

public:

};
