// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BasicWaterVolume.generated.h"

class AC_BaseAI;

UCLASS()
class MYPROJECT_API AC_BasicWaterVolume : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* BoxComp;
	
private:
	AC_BasicWaterVolume();

	virtual void BeginPlay() override;

	virtual void Tick(float DelaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AC_BaseAI* AI;

	TArray<AC_BaseAI*> AIArray;


};
