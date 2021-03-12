// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_ReactorBeam.generated.h"

UCLASS()
class MYPROJECT_API AC_ReactorBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_ReactorBeam();

protected:

	virtual void BeginPlay() override;

	void BeginCorruption();

	void BecomeCorrupted();

	UPROPERTY(EditDefaultsOnly, Category = "Beam")
	class UNiagaraComponent* BeamComp;

	UPROPERTY(EditInstanceOnly, Category = "Beam")
	AActor* TargetActor;

	// Exposed Variables

	// The location of where the beam will strike 
	UPROPERTY(EditAnywhere, Category = "Beam")
	FVector BeamTargetLocation;

	// The max area the beam can hit
	UPROPERTY(EditAnywhere, Category = "Beam")
	float MaxBeamRange;

	// The min area the beam can hit
	UPROPERTY(EditAnywhere, Category = "Beam")
	float MinBeamRange;

	// The time it takes the lightning to hit a new target location
	UPROPERTY(EditAnywhere, Category = "Beam")
	float LightningFrequency;

	FTimerHandle ChangeTargetLocationHandle;

	// Beam spawn

	void SpawnEffects();

	UPROPERTY(EditDefaultsOnly, Category = "Beam")
	class UNiagaraSystem* SparksEffect;

	// Beam Colour

	// Default beam colour
	UPROPERTY(EditInstanceOnly, Category = "Beam")
	FLinearColor color;

	// The curve that controlls how the colour will change
	UPROPERTY(EditDefaultsOnly, Category = "Beam")
	UCurveFloat* FColourChangeCurve;

	UTimelineComponent* ColourChangeTimeline;

	FOnTimelineFloat ColourChangeInterpFunction{};

	UFUNCTION()
	void ColourChangeTimelineFloatReturn(float Alpha);




};
