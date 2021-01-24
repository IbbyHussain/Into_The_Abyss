// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_Ability2.generated.h"

UCLASS()
class MYPROJECT_API AC_Ability2 : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Ability2();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability2")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Ability2")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability2")
	class UNiagaraComponent* Ability2Effect;

	void DeSpawnParticleEffect();

	void ParticleFadeOut();

	class AC_BaseAI* BaseAI;

	TArray<class AC_BaseAI*> BaseAIArray;

	AActor* HitAk;

	UPrimitiveComponent* Prim;

	AC_BaseAI* AI;

	// Material Fade Out.

	// The curve that controlls how the material will fade out
	UPROPERTY(EditDefaultsOnly, Category = "Material Fade")
	UCurveFloat* FMaterialFadeCurve;

	// The material that will fade out
	UPROPERTY(EditDefaultsOnly, Category = "Material Fade")
	UMaterialInterface* ChestMaterialGlow;
	
	UMaterialInstanceDynamic* DynamicChestMaterialGlow;

	UTimelineComponent* MaterialFadeTimeline;

	FOnTimelineFloat MaterialFadeInterpFunction{};

	UFUNCTION()
	void MaterialFadeTimelineFloatReturn(float Alpha);

	void DestroyThis();

};
