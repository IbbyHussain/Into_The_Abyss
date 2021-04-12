// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "C_SpikeDoor.generated.h"



UCLASS()
class MYPROJECT_API AC_SpikeDoor : public AC_StaticMeshActor
{
	GENERATED_BODY()
public:
	void PlayOpenDoorAnimation();

protected:
	AC_SpikeDoor();

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FSpikeCurve;

	UTimelineComponent* SpikeTimeline;

	FOnTimelineFloat SpikeInterpFunction{};

	UFUNCTION()
	void SpikeTimelineFloatReturn(float Value);

	virtual void BeginPlay() override;

	float DefaultMeshHeight;

	float SwimMeshHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* DoorOpenSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	FVector TargetLocation;

	UPROPERTY(EditInstanceOnly, Category = "Sound")
	bool bPlaySound;
private:

};
