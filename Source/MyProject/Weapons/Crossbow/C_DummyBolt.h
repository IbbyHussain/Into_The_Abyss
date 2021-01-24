
#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "C_DummyBolt.generated.h"

UCLASS()
class MYPROJECT_API AC_DummyBolt : public AC_StaticMeshActor
{
	GENERATED_BODY()

public:
	AC_DummyBolt();

	USceneComponent* RootComp;

	// controls if a dummy bolt can be spawned
	bool bCanBeSpawned;
};
