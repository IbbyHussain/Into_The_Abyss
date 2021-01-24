// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeMechanicManagerClass.generated.h"

class AC_StaticMeshActor;
class AC_SkeletalMeshActor;
class AC_SkeletalMeshAnimActor;
class AC_ChestActorBase;
class AC_DestructibleMeshBase;

UCLASS()
class MYPROJECT_API ATimeMechanicManagerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeMechanicManagerClass();

	UFUNCTION(BlueprintCallable)
	void SetManagerFuture();

	UFUNCTION(BlueprintCallable)
	void SetManagerPast();

private:

	TArray<AC_StaticMeshActor*> StaticMeshActorArray;

	TArray<AC_SkeletalMeshActor*> SkeletalMeshActorArray;

	TArray<AC_SkeletalMeshAnimActor*> SkeletalMeshAnimActorArray;

	TArray<AC_ChestActorBase*> ChestActorBaseArray;

	TArray<AC_DestructibleMeshBase*> DestructibleMeshArray;



	AC_StaticMeshActor* StaticMeshActor;

	AC_SkeletalMeshActor* SkeletalMeshActor;

	AC_SkeletalMeshAnimActor* SkeletalMeshAnimActor;

	AC_ChestActorBase* ChestActorBase;

	AC_DestructibleMeshBase* DestructibleMeshBase;




};
