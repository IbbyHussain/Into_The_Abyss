// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ReactorBeam.generated.h"

UCLASS()
class MYPROJECT_API AC_ReactorBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_ReactorBeam();

protected:

	virtual void BeginPlay() override;

	void BecomeCorrupted();

	UPROPERTY(EditDefaultsOnly, Category = "Beam")
	class UNiagaraComponent* BeamComp;

	UPROPERTY(EditAnywhere, Category = "Beam")
	FVector BeamTargetLocation;

	UPROPERTY(EditAnywhere, Category = "Beam")
	float MaxBeamRange;

	UPROPERTY(EditAnywhere, Category = "Beam")
	float MinBeamRange;

	FTimerHandle ChangeTargetLocationHandle;
};
