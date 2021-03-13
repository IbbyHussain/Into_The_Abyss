#pragma once
#include "CoreMinimal.h"
#include "MyProject/ManagerClasses/C_BaseManagerClass.h"
#include "C_TheLabLevel_ManagerClass.generated.h"

class AC_BaseManagerClass;
class AC_WarningLight;
class AC_ReactorBeam;

UCLASS()
class MYPROJECT_API AC_TheLabLevel_ManagerClass : public AC_BaseManagerClass
{
	GENERATED_BODY()
	
public:	
	AC_TheLabLevel_ManagerClass();

	UPROPERTY(EditInstanceOnly)
	TArray<AC_BaseManagerClass*> ManagerArray;

	void Update();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditInstanceOnly)
	TArray<AC_WarningLight*> WarningLightArray;

	// Beams

	UPROPERTY(EditInstanceOnly)
	TArray<AC_ReactorBeam*> CoreBeamArray;

	UPROPERTY(EditInstanceOnly)
	TArray<AC_ReactorBeam*> MinorBeamArray;

	FTimerHandle ActivateBeamHandle;

	int BeamCounter;

	void ActivateSecondBeam();
};
