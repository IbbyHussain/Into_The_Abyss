// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RightHandMagic.generated.h"

UCLASS()
class MYPROJECT_API AC_RightHandMagic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_RightHandMagic();

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
