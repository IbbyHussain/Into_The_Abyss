// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SkeletalMeshAnimActor.generated.h"

UCLASS()
class MYPROJECT_API AC_SkeletalMeshAnimActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_SkeletalMeshAnimActor();

	UFUNCTION(BlueprintCallable)
	void SetPast();

	UFUNCTION(BlueprintCallable)
	void SetFuture();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Mesh")
	USkeletalMeshComponent* PastMesh;

	UPROPERTY(EditInstanceOnly, Category = "Mesh")
	USkeletalMeshComponent* FutureMesh;

};
