// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DestructibleMeshBase.generated.h"

class UDestructibleComponent;
class UDestructibleMesh;

UCLASS()
class MYPROJECT_API AC_DestructibleMeshBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_DestructibleMeshBase();

	UFUNCTION(BlueprintCallable)
	void SetPast();

	UFUNCTION(BlueprintCallable)
	void SetFuture();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UDestructibleComponent* MeshComp;

protected:

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UDestructibleMesh* PastMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UDestructibleMesh* FutureMesh;



};
