// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SkeletalMeshAnimActor.h"

// Sets default values
AC_SkeletalMeshAnimActor::AC_SkeletalMeshAnimActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PastMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Past Mesh"));

	FutureMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Future Mesh"));
	FutureMesh->SetVisibility(false);

}

void AC_SkeletalMeshAnimActor::SetFuture()
{
	FutureMesh->SetVisibility(true);
	PastMesh->SetVisibility(false);
}

void AC_SkeletalMeshAnimActor::SetPast()
{
	PastMesh->SetVisibility(true);
	FutureMesh->SetVisibility(false);
}

