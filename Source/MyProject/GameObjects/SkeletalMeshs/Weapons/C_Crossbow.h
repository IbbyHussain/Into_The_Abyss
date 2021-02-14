// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_SkeletalMeshActor.h"
#include "Components/TimelineComponent.h"
#include "C_Crossbow.generated.h"



class AC_Crossbowbolt;
class AC_DummyBolt;
class UC_CrossBowBoltTracker;

UCLASS()
class MYPROJECT_API AC_Crossbow : public AC_SkeletalMeshActor
{
	GENERATED_BODY()

	AC_Crossbow();

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Spawn bolt

	void SpawnBolt(FVector EndLocation);

	void SpawnBoltAI(FVector EndLoc);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	TSubclassOf<AC_Crossbowbolt> CrossbowboltClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Crossbow")
	TSubclassOf<AC_Crossbowbolt> AICrossbowboltClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,  Category = "Crossbow")
	AC_Crossbowbolt* Crossbowbolt;

	FName CrossbowboltSocket;

	UFUNCTION(BlueprintCallable)
	void ResetBolts();

	// Spawn a dummy bolt, which is used for reload sequence

	void ReloadCrossbow();

	void SpawnDummybolt(FName SocketName, TSubclassOf<AC_DummyBolt> DummyClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	TSubclassOf<AC_DummyBolt> DummyBoltClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	AC_DummyBolt* DummyBolt;

	FName DummyBoltSocket;

	// Destroy Dummy Bolt

	void DestroyDummyBolt();

	// Dummy Bolt Timeline

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FSlideCurve;

	UTimelineComponent* SlideTimeline;

	FOnTimelineFloat SlideInterpFunction{};

	UFUNCTION()
	void SlideTimelineFloatReturn(float Value);

	void PlayTimeline();

	// Bolts

	void UpdateNumberofBolts(int32 Num);

	UFUNCTION(BlueprintCallable)
	void SaveBolts();

	UFUNCTION(BlueprintCallable)
	void LoadBolts();

	// Bolt Types

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	TArray<TSubclassOf<AC_Crossbowbolt>> BoltsArray;

	// Dummy Bolt Types
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	TArray<TSubclassOf<AC_DummyBolt>> DummyBoltsArray;

	// Bolt Icon Types

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow | BoltIcon")
	TArray<TSubclassOf<UC_CrossBowBoltTracker>> BoltIconArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow | BoltIcon")
	TSubclassOf<UC_CrossBowBoltTracker> BoltIconClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow | BoltIcon")
	UC_CrossBowBoltTracker* BoltIcon;

};
