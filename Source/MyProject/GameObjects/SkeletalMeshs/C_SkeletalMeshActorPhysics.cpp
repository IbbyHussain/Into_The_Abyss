// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SkeletalMeshActorPhysics.h"

AC_SkeletalMeshActorPhysics::AC_SkeletalMeshActorPhysics()
{
	MeshComp->SetSimulatePhysics(true);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}