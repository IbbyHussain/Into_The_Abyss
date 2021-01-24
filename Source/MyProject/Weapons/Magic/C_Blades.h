// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Blades.generated.h"

UCLASS()
class MYPROJECT_API AC_Blades : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Blades();

	UPROPERTY(EditDefaultsOnly, Category = "Ability2")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Ability2")
	class UBoxComponent* BoxComp;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
