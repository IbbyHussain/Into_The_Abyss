// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MoveableObjectManager.h"
#include "EngineUtils.h"
#include "MyProject/GameObjects/StaticMeshs/Interactables/Puzzles/C_MoveableObject.h"

// Sets default values
AC_MoveableObjectManager::AC_MoveableObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AC_MoveableObjectManager::EnableConstraints()
{
	UWorld* World = GetWorld();
	for (TActorIterator<AC_MoveableObject> It(World, AC_MoveableObject::StaticClass()); It; ++It)
	{
		MoveableObject = *It;
		if (MoveableObject != NULL)
		{
			MoveableObjectArray.Add(MoveableObject);
			MoveableObject->EnablePhysicsConstraint();
		}
	}

}


