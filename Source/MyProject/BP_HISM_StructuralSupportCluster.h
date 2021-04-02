
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_HISM_StructuralSupportCluster.generated.h"

UCLASS()
class MYPROJECT_API ABP_HISM_StructuralSupportCluster : public AActor
{
	GENERATED_BODY()
	
public:	

	ABP_HISM_StructuralSupportCluster();

	virtual void BeginPlay() override;

	class UHierarchicalInstancedStaticMeshComponent* HISMComp;

	UPROPERTY(EditInstanceOnly, Category = "Exposed")
	TArray<FTransform> InstanceTransformArray;

	void SpawnInstances();

};
