// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DecreaseBreathVolume.generated.h"

class UBoxComponent;
class AC_PlayerCharacter;

UCLASS()
class MYPROJECT_API AC_DecreaseBreathVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_DecreaseBreathVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Volume")
	UBoxComponent* BreathVolume;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Decrease Breath
	bool bShouldDecreaseBreath;

	FTimerHandle DecreaseBreathHandle;

	void DecreaseBreath();

	float TimeBeforeDrowning;

	float RateOfBreath;

	//Regen Breath

	FTimerHandle RegenBreathHandle;

	void RegenBreath();

	void UpdateBreathVisibility();

	bool bHasFadedOut;

	UPROPERTY(EditAnywhere, Category = "Volume")
	USceneComponent* Root;

};
