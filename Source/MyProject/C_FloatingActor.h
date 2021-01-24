// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h" 
#include "C_FloatingActor.generated.h"

class UTimelineComponent;

UCLASS()
class MYPROJECT_API AC_FloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_FloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UTimelineComponent* MyTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* FCurve;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

	UFUNCTION()
	void TimelineFloatReturn(float Value);

	UFUNCTION()
	void OnTimelineFinished();

	//declare delegate
	FOnTimelineFloat InterpFunction{};

	FOnTimelineEvent TimelineFinished{};

};
