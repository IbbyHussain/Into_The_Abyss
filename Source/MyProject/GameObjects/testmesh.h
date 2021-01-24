// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "testmesh.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API Atestmesh : public AC_StaticMeshActor
{
	GENERATED_BODY()

public:
	Atestmesh();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Pitch;
	UPROPERTY(EditAnywhere)
	float Yaw;
	UPROPERTY(EditAnywhere)
	float Roll;
	
	//timeline 1
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FCurve;

	//timeline 1
	// The timeline component
	UTimelineComponent* Timeline1;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat Timeline1InterpFunction{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline1FloatReturn(float Value);




	//timeline 2
	// The timeline component
	UTimelineComponent* Timeline2;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat Timeline2InterpFunction{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline2FloatReturn(float Value);




	//timeline 3
	// The timeline component
	UTimelineComponent* Timeline3;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat Timeline3InterpFunction{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline3FloatReturn(float Value);




	//timeline 4
	// The timeline component
	UTimelineComponent* Timeline4;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat Timeline4InterpFunction{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline4FloatReturn(float Value);


	FTimerHandle RotateHandle;

	float Timeline1Value;
	float Timeline2Value;
	float Timeline3Value;

	void Reset();
	void Reset2();
	void Reset3();

};
