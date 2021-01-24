
#include "C_DummyBolt.h"
#include "Particles/ParticleSystemComponent.h"

AC_DummyBolt::AC_DummyBolt()
{
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root comp"));
	RootComponent = RootComp;

	MeshComp->SetupAttachment(RootComp);
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	MeshComp->SetRelativeLocation(FVector(6.0f, 0.0f, 0.0f));

	FRotator Rot = FRotator(0.0f, -90.0f, 0.0f);
	MeshComp->SetRelativeRotation(Rot.Quaternion());

	bCanBeSpawned = true;
}