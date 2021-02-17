// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_RollerAI.generated.h"

UCLASS()
class MYPROJECT_API AC_RollerAI : public APawn
{
	GENERATED_BODY()

public:

	AC_RollerAI();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* MeshComp;

protected:

	virtual void BeginPlay() override;

private:

	// Next point in navigation path
	FVector NextPathPoint;

	FVector GetNextPathPoint();

	UPROPERTY(EditDefaultsOnly, Category = "Roller AI")
	float MovementForce;

	UPROPERTY(EditDefaultsOnly, Category = "Roller AI")
	float RequiredDistanceToTarget;

	bool bUseVelocityChange;
	
	


};
