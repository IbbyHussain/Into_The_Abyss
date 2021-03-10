// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_WarningLight.generated.h"

UCLASS()
class MYPROJECT_API AC_WarningLight : public AActor
{
	GENERATED_BODY()
	
public:	

	AC_WarningLight();

	// called in manager class for lab level sequence
	void StartPulse();

protected:
	
	virtual void BeginPlay() override;

	void Pulse();


	// Timer used to pulse 
	FTimerHandle PulseHandle;

	// Dynamic material for pulse 
	UMaterialInstanceDynamic* MatInst;

	// Material of warning light
	UPROPERTY(EditDefaultsOnly, Category = "Material Fade")
	UMaterialInterface* WarningLightGlow;

	// The sound effect that will be played
	UPROPERTY(EditDefaultsOnly, Category = "Light")
	USoundBase* WarningLightSound;

	UPROPERTY(EditDefaultsOnly, Category = "Light")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Light")
	class UPointLightComponent* PointLight;



};
