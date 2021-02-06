// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "Components/TimelineComponent.h"
#include "C_SavageAI.generated.h"

UCLASS()
class MYPROJECT_API AC_SavageAI : public AC_MeleeAI
{
	GENERATED_BODY()

	AC_SavageAI();

public:

	virtual void ChangeAIColour() override;

	virtual void BeginPlay() override;

// SPECIAL ATTACK

	// BECOME ENRAGED

	UFUNCTION(BlueprintCallable)
	void BecomeEnraged();

	UPROPERTY(EditDefaultsOnly, Category = "Special Attack")
	USoundBase* EnragedSound;

	UPROPERTY(EditDefaultsOnly, Category = "Special Attack")
	UAnimMontage* EnragedMontage;

	// SPAWN INDICATOR

	class AC_StaticMeshActor* SavageIndicator;

	UPROPERTY(EditDefaultsOnly, Category = "Special Attack")
	TSubclassOf<class AC_StaticMeshActor> SavageIndicatorClass;

	void SpawnSavageIndicator();

	// JUMP START 

	UFUNCTION(BlueprintCallable)
	void JumpStart();

	UPROPERTY(EditAnywhere, Category = "Special Attack")
	UCurveFloat* FJumpCurve;

	// The timeline component
	UTimelineComponent* JumpStartTimeline;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat JumpStartInterpFunction{};
	FOnTimelineEvent JumpStartTimelineFinished{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void JumpStartTimelineFloatReturn(float Value);

	// The function to be binded to finish
	UFUNCTION()
	void OnJumpStartTimelineFinished();

	// LAND

	void Land();

	FTimerHandle LandHandle;

	UPROPERTY(EditAnywhere, Category = "Special Attack")
	UCurveFloat* FLandCurve;

	// The timeline component
	UTimelineComponent* LandTimeline;

	// delegates for the timeline (update and finish)
	FOnTimelineFloat LandInterpFunction{};
	FOnTimelineEvent LandTimelineFinished{};

	// The function to be binded to interp (update)
	UFUNCTION()
	void LandTimelineFloatReturn(float Value);

	// The function to be binded to finish
	UFUNCTION()
	void OnLandTimelineFinished();

	UPROPERTY(EditDefaultsOnly, Category = "Special Attack")
	UAnimMontage* LandMontage;

	FTimerHandle ResetMovementHandle;

	void ResetMovement();
};
