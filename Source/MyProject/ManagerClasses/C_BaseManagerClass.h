#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseManagerClass.generated.h"

UCLASS()
class MYPROJECT_API AC_BaseManagerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_BaseManagerClass();

	bool bIsComplete;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
