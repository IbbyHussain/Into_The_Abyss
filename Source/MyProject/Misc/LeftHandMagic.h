// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeftHandMagic.generated.h"

UCLASS()
class MYPROJECT_API ALeftHandMagic : public AActor
{
	GENERATED_BODY()
	
public:	
	ALeftHandMagic();

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	class UParticleSystemComponent* Effect;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	UParticleSystemComponent* FireEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	UParticleSystemComponent* IceEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	UParticleSystemComponent* VoidEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	UParticleSystemComponent* AirEffect;

	void ShowDefaultEffect();

	void ShowFireEffect();

	void ShowIceEffect();

	void ShowVoidEffect();

	void ShowAirEffect();

	void Visible();

	void InVisible();

};
