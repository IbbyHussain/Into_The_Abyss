// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_BlackHole.generated.h"


class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API AC_BlackHole : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	/* Inner sphere destroys the overlapping components */
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* InnerSphereComponent;

	/* Outer sphere pulls components (that are physically simulating) towards the centre of the actor */
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* OuterSphereComponent;

	// Marked with ufunction to bind to overlap event
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Growth - The black hole will grow over time using a timeline

	UPROPERTY(EditDefaultsOnly, Category = "Timeline")
	UCurveFloat* FGrowthCurve;

	// The timeline component
	UTimelineComponent* GrowthTimeline;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat GrowthInterpFunction{};
	FOnTimelineEvent GrowthTimelineFinished{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void GrowthTimelineFloatReturn(float Value);

	// The function to be binded to finish
	UFUNCTION()
	void OnGrowthTimelineFinished();

	// The amount to increase the blackholes size
	UPROPERTY(EditAnywhere, Category = "Timeline")
	float Scale;

	FVector DefaultScale;

	FVector FinalScale;

	// Growth - second time

	UTimelineComponent* Growth2Timeline;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat Growth2InterpFunction{};

	UFUNCTION()
	void Growth2TimelineFloatReturn(float Value);

	UPROPERTY(EditDefaultsOnly, Category = "Timeline")
	UCurveFloat* FGrowth2Curve;

	FVector FinalScale2;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float Scale2;

	void PlayGrowth2();

	UPROPERTY(EditDefaultsOnly, Category = "Exposed | BlackHole")
	TSubclassOf<UCameraShake> BlackHoleCameraShake;

	// Misc

	class AC_PlayerCharacter* Player;

public:	

	AC_BlackHole();

	virtual void Tick(float DeltaTime) override;
};
