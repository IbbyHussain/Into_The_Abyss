// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeMechanicManagerClass.h"
#include "EngineUtils.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "MyProject/GameObjects/C_SkeletalMeshActor.h"
#include "MyProject/GameObjects/C_SkeletalMeshAnimActor.h"
#include "MyProject/GameObjects/SkeletalMeshs/Chests/C_ChestActorBase.h"
#include "MyProject/GameObjects/SkeletalMeshs/Chests/C_ChestActorBase.h"
#include "MyProject/GameObjects/DestructibleMeshs/C_DestructibleMeshBase.h"

// Sets default values
ATimeMechanicManagerClass::ATimeMechanicManagerClass()
{

}

void ATimeMechanicManagerClass::SetManagerFuture()
{
	//Static meshss
	UWorld* World = GetWorld();
	for (TActorIterator<AC_StaticMeshActor> It(World, AC_StaticMeshActor::StaticClass()); It; ++It)
	{
		StaticMeshActor = *It;
		if (StaticMeshActor != NULL)
		{
			StaticMeshActorArray.Add(StaticMeshActor);
			StaticMeshActor->SetFuture();
		}
	}

	//Skeletal meshs
	for (TActorIterator<AC_SkeletalMeshActor> It(World, AC_SkeletalMeshActor::StaticClass()); It; ++It)
	{
		SkeletalMeshActor = *It;
		if (SkeletalMeshActor != NULL)
		{
			SkeletalMeshActorArray.Add(SkeletalMeshActor);
			SkeletalMeshActor->SetFuture();
		}
	}

	//Skeletal Meshs with animations
	for (TActorIterator<AC_SkeletalMeshAnimActor> It(World, AC_SkeletalMeshAnimActor::StaticClass()); It; ++It)
	{
		SkeletalMeshAnimActor = *It;
		if (SkeletalMeshAnimActor != NULL)
		{
			SkeletalMeshAnimActorArray.Add(SkeletalMeshAnimActor);
			SkeletalMeshAnimActor->SetFuture();
		}
	}

	// Chest glow plane
	for (TActorIterator<AC_ChestActorBase> It(World, AC_ChestActorBase::StaticClass()); It; ++It)
	{
		ChestActorBase = *It;
		if (ChestActorBase != NULL)
		{
			ChestActorBaseArray.Add(ChestActorBase);
			ChestActorBase->FuturePlaneVisibility();
		}
	}

	// Destructible Meshs
	for (TActorIterator<AC_DestructibleMeshBase> It(World, AC_DestructibleMeshBase::StaticClass()); It; ++It)
	{
		DestructibleMeshBase = *It;
		if (DestructibleMeshBase != NULL)
		{
			DestructibleMeshArray.Add(DestructibleMeshBase);
			DestructibleMeshBase->SetFuture();
		}
	}


}

void ATimeMechanicManagerClass::SetManagerPast()
{
	//Static meshs
	UWorld* World = GetWorld();
	for (TActorIterator<AC_StaticMeshActor> It(World, AC_StaticMeshActor::StaticClass()); It; ++It)
	{
		StaticMeshActor = *It;
		if (StaticMeshActor != NULL)
		{
			StaticMeshActorArray.Add(StaticMeshActor);
			StaticMeshActor->SetPast();
		}
	}

	//Skeletal meshs
	for (TActorIterator<AC_SkeletalMeshActor> It(World, AC_SkeletalMeshActor::StaticClass()); It; ++It)
	{
		SkeletalMeshActor = *It;
		if (SkeletalMeshActor != NULL)
		{
			SkeletalMeshActorArray.Add(SkeletalMeshActor);
			SkeletalMeshActor->SetPast();
		}
	}

	//Skeletal Meshs with animations
	for (TActorIterator<AC_SkeletalMeshAnimActor> It(World, AC_SkeletalMeshAnimActor::StaticClass()); It; ++It)
	{
		SkeletalMeshAnimActor = *It;
		if (SkeletalMeshAnimActor != NULL)
		{
			SkeletalMeshAnimActorArray.Add(SkeletalMeshAnimActor);
			SkeletalMeshAnimActor->SetPast();
		}
	}

	// Chest glow plane
	for (TActorIterator<AC_ChestActorBase> It(World, AC_ChestActorBase::StaticClass()); It; ++It)
	{
		ChestActorBase = *It;
		if (ChestActorBase != NULL)
		{
			ChestActorBaseArray.Add(ChestActorBase);
			ChestActorBase->PastPlaneVisibility();
		}
	}

	// Destructible Meshs
	for (TActorIterator<AC_DestructibleMeshBase> It(World, AC_DestructibleMeshBase::StaticClass()); It; ++It)
	{
		DestructibleMeshBase = *It;
		if (DestructibleMeshBase != NULL)
		{
			DestructibleMeshArray.Add(DestructibleMeshBase);
			DestructibleMeshBase->SetPast();
		}
	}
}


