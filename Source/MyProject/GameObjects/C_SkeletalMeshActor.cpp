// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SkeletalMeshActor.h"

// Sets default values
AC_SkeletalMeshActor::AC_SkeletalMeshActor()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	RootComponent = MeshComp;
}

void AC_SkeletalMeshActor::SetPast()
{
	UE_LOG(LogTemp, Log, TEXT("PAST"));
	MeshComp->SetSkeletalMesh(PastMesh);
}

void AC_SkeletalMeshActor::SetFuture()
{
	UE_LOG(LogTemp, Log, TEXT("FUTURE"));
	MeshComp->SetSkeletalMesh(FutureMesh);
}

