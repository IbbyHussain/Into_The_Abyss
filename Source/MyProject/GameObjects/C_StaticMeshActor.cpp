// Fill out your copyright notice in the Description page of Project Settings.


#include "C_StaticMeshActor.h"

// Sets default values
AC_StaticMeshActor::AC_StaticMeshActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
}

void AC_StaticMeshActor::SetPast()
{
	UE_LOG(LogTemp, Log, TEXT("PAST"));
	MeshComp->SetStaticMesh(PastMesh);
}

void AC_StaticMeshActor::SetFuture()
{
	UE_LOG(LogTemp, Log, TEXT("FUTURE"));
	MeshComp->SetStaticMesh(FutureMesh);
}

