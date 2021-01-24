#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MagicEffects.generated.h"

UCLASS()
class MYPROJECT_API AC_MagicEffects : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AC_MagicEffects();

private:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	

};
