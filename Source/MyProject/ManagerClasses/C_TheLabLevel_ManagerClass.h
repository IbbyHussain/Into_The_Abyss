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

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeLighting();

	UFUNCTION(BlueprintCallable)
	void SpawnBlackHole();

	UFUNCTION(BlueprintCallable)
	void StartBeamCorruption();

	UFUNCTION(BlueprintCallable)
	void StartMinorBeamCorruption();

	UFUNCTION(BlueprintCallable)
	void ActivateFirstBeam();

	UFUNCTION(BlueprintImplementableEvent)
	void PuzzlesAreComplete();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



private:

	float TimeBetweenSequences;

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

	UPROPERTY()
	AC_BlackHole* BlackHole;

	UPROPERTY(EditDefaultsOnly, Category = "Exposed | Blackhole")
	TSubclassOf<AC_BlackHole> BlackHoleClass;

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Blackhole")
	AActor* BlackHoleSpawnPoint;

	// Misc

	UPROPERTY(EditDefaultsOnly, Category = "Exposed | Defaults")
	TSubclassOf<UCameraShake> CameraShake;

	UPROPERTY(EditDefaultsOnly, Category = "Exposed | BlackHole")
	TSubclassOf<UCameraShake> BlackHoleCameraShake;

	void PlayCameraShake();

	// Start Cinematic

	UPROPERTY(EditInstanceOnly, Category = "Exposed | Defaults")
	class AC_BaseQuest* MainQuest;


	
};
