// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseCustomisedAI.h"
#include "C_SummonerAI.generated.h"

UCLASS()
class MYPROJECT_API AC_SummonerAI : public AC_BaseCustomisedAI
{
	GENERATED_BODY()

	AC_SummonerAI();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Summoner")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Summoner")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = "Summoner")
	TSubclassOf <class AC_SummonerProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Summoner")
	TSubclassOf <class AC_RollerAI> RollerAIClass;

public:

	virtual void OnDeath() override;

	void SummonerBasicAttack();

	void SummonerSpecialAttack();

	UPROPERTY(EditAnywhere, Category = "Summoner")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Summoner")
	UParticleSystem* TeleportParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Summoner")
	USoundBase* TeleportSound;

	void TeleportToLocationEffects();

};
