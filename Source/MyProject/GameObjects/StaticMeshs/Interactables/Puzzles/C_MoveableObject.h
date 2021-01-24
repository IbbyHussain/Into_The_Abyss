// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/StaticMeshs/C_StaticMeshActorPhysics.h"
#include "C_MoveableObject.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AC_MoveableObject : public AC_StaticMeshActorPhysics
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void EnablePhysicsConstraint();
protected:

	AC_MoveableObject();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// The box collision for the Y axis
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	UBoxComponent* YBox;

	// The box collision for the X axis
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	UBoxComponent* XBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics")
	class UPhysicsConstraintComponent* PhysicsComp;
	
	// The sound to be played whilst this object is being pushed
	UPROPERTY(EditInstanceOnly, Category = "Sound")
	USoundBase* MovingSound;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* MovingSoundComponent;

	UFUNCTION(BlueprintCallable)
	float CalculateVelocity(float Velocity);

	// YBox Collision Events
	UFUNCTION()
	void OnOverlapYBoxBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapYBoxEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// XBox Collision Events
	UFUNCTION()
	void OnOverlapXBoxBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapXBoxEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	class AC_PlayerCharacter* Player;
};
