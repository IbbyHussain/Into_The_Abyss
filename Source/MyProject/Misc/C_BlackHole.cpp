// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"

AC_BlackHole::AC_BlackHole()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComponent->SetSphereRadius(100);
	InnerSphereComponent->SetupAttachment(MeshComp);

	// Bind to Event
	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_BlackHole::OverlapInnerSphere);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComponent->SetSphereRadius(3000);
	OuterSphereComponent->SetupAttachment(MeshComp);

	// Timeline delegate setup

	GrowthTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("GrowthTimeline"));
	// Here is where we bind our delegates to our functions via function names
	GrowthInterpFunction.BindUFunction(this, FName("GrowthTimelineFloatReturn"));
	GrowthTimelineFinished.BindUFunction(this, FName("OnGrowthTimelineFinished"));

	Scale = 1.01;

}

void AC_BlackHole::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Growth timeline further setup
	if (FGrowthCurve)
	{
		// Now we set the functions and some values.
		GrowthTimeline->AddInterpFloat(FGrowthCurve, GrowthInterpFunction, FName("Alpha"));
		GrowthTimeline->SetTimelineFinishedFunc(GrowthTimelineFinished);
		GrowthTimeline->SetLooping(false);
	}

	DefaultScale = GetActorScale3D();

	FinalScale = GetActorScale3D() * Scale;

	GrowthTimeline->Play();

}

void AC_BlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find all overlapping components that can collide and may be physically simulating.
	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphereComponent->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			// the component we are looking for! It needs to be simulating in order to apply forces.

			const float SphereRadius = OuterSphereComponent->GetScaledSphereRadius();
			const float ForceStrength = -2000; // Negative value to make it pull towards the origin instead of pushing away

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

void AC_BlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != Player)
	{
		OtherActor->Destroy();
	}
}

void AC_BlackHole::GrowthTimelineFloatReturn(float Value)
{
	SetActorScale3D(FVector(FMath::Lerp(DefaultScale, FinalScale, Value)));
}

void AC_BlackHole::OnGrowthTimelineFinished()
{

}