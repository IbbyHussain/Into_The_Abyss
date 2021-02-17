
#include "C_RollerAI.h"
#include "Components/StaticMeshComponent.h"

AC_RollerAI::AC_RollerAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetCanEverAffectNavigation(false);
	RootComponent = MeshComp;

}

void AC_RollerAI::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_RollerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
