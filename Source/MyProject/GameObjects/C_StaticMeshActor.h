// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_StaticMeshActor.generated.h"

UCLASS()
class MYPROJECT_API AC_StaticMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_StaticMeshActor();

protected:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* PastMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* FutureMesh;

public:
	UFUNCTION(BlueprintCallable)
	void SetPast();

	UFUNCTION(BlueprintCallable)
	void SetFuture();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MeshComp;
	
};
