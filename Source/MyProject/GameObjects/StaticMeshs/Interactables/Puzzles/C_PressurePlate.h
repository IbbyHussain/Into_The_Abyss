// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "C_PressurePlate.generated.h"

class AC_MoveableObject;

UCLASS()
class MYPROJECT_API AC_PressurePlate : public AC_StaticMeshActor
{
	GENERATED_BODY()

public:
	bool bIsActivated;

protected:
	AC_PressurePlate();

	virtual void BeginPlay() override;

	//Material of the pressure plate
	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	UMaterialInterface* PressurePlateMaterial;

	// The box collision 
	UPROPERTY(EditDefaultsOnly, Category = "Puzzle")
	class UBoxComponent* BoxComp;

	// The object needed to be on the pressure plate
	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	AC_MoveableObject* MoveableObject;

	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	USoundBase* PuzzleSound;

	//Determines if the pressure plate can be activated by the player
	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	bool bPlayerActivateable;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	//Dynamic material ref
	UMaterialInstanceDynamic* DynamicPressurePlateMaterial;

	class AC_PlayerCharacter* Player;

	void Activated();

	void DeActivated();
};
