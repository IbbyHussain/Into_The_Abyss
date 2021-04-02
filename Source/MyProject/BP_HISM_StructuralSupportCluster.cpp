// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_HISM_StructuralSupportCluster.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

ABP_HISM_StructuralSupportCluster::ABP_HISM_StructuralSupportCluster()
{
	HISMComp = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISM"));
	HISMComp->SetWorldScale3D(FVector(2.0f));
	HISMComp->SetMobility(EComponentMobility::Static);

}

void ABP_HISM_StructuralSupportCluster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABP_HISM_StructuralSupportCluster::SpawnInstances()
{
	for (auto i : InstanceTransformArray)
	{
		FTransform InstanceTransform;
		InstanceTransform.SetLocation(InstanceTransform.GetLocation() / 2.0f);
		HISMComp->AddInstance(InstanceTransform);
	}
}