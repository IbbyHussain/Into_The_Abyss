#pragma once
#include "CoreMinimal.h"
#include "MyProject/ManagerClasses/C_BaseManagerClass.h"
#include "C_TheLabLevel_ManagerClass.generated.h"

class AC_BaseManagerClass;
class AC_WarningLight;
class AC_ReactorBeam;
class AC_BlackHole;

UCLASS()
class MYPROJECT_API AC_TheLabLevel_ManagerClass : public AC_BaseManagerClass
{
	GENERATED_BODY()
	
public:	
	AC_TheLabLevel_ManagerClass();

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Defaults")
	TArray<AC_BaseManagerClass*> ManagerArray;

	void Update();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



private:

	UPROPERTY(EditInstanceOnly, Category = "Exposed | WarningLights")
	TArray<AC_WarningLight*> WarningLightArray;

	// Beams

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Beams")
	TArray<AC_ReactorBeam*> CoreBeamArray;

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Beams")
	TArray<AC_ReactorBeam*> MinorBeamArray;

	FTimerHandle ActivateBeamHandle;

	int BeamCounter;

	void ActivateSecondBeam();

	// Blackhole

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Blackhole")
	TArray<AActor*> PhysicsActorsArray;

	UFUNCTION()
	void SpawnBlackHole();

	AC_BlackHole* BlackHole;

	UPROPERTY(EditDefaultsOnly, Category = "Exposed | Blackhole")
	TSubclassOf<AC_BlackHole> BlackHoleClass;

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Blackhole")
	AActor* BlackHoleSpawnPoint;
};
