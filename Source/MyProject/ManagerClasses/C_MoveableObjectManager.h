// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MoveableObjectManager.generated.h"

UCLASS()
class MYPROJECT_API AC_MoveableObjectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MoveableObjectManager();

	void EnableConstraints();

private:
	TArray<class AC_MoveableObject*> MoveableObjectArray;

	class AC_MoveableObject* MoveableObject;



};
