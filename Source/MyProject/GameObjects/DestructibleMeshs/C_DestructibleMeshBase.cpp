// Fill out your copyright notice in the Description page of Project Settings.


#include "C_DestructibleMeshBase.h"
#include "DestructibleComponent.h"


AC_DestructibleMeshBase::AC_DestructibleMeshBase()
{
	MeshComp = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Mesh Comp"));
}


void AC_DestructibleMeshBase::SetPast()
{
	UE_LOG(LogTemp, Log, TEXT("PAST"));
	MeshComp->SetDestructibleMesh(PastMesh);
}

void AC_DestructibleMeshBase::SetFuture()
{
	UE_LOG(LogTemp, Log, TEXT("FUTURE"));
	MeshComp->SetDestructibleMesh(FutureMesh);
}




