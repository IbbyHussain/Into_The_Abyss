// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SkeletalMeshActor.generated.h"

UCLASS()
class MYPROJECT_API AC_SkeletalMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SkeletalMeshActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* MeshComp;

protected:

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMesh* PastMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMesh* FutureMesh;

public:
	UFUNCTION(BlueprintCallable)
	void SetPast();

	UFUNCTION(BlueprintCallable)
	void SetFuture();
};
