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

	Growth2Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("GrowthTimeline2"));
	Growth2InterpFunction.BindUFunction(this, FName("Growth2TimelineFloatReturn"));

	Scale = 8.0f;

	Scale2 = 16.0;

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

	if(FGrowth2Curve)
	{
		// Now we set the functions and some values.
		Growth2Timeline->AddInterpFloat(FGrowth2Curve, Growth2InterpFunction, FName("Bravo"));
		Growth2Timeline->SetLooping(false);
	}

	DefaultScale = GetActorScale3D();

	FinalScale = GetActorScale3D() * Scale;

	GrowthTimeline->PlayFromStart();

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
	if (OtherActor && OtherActor != Player && OtherActor != this)
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
	UE_LOG(LogTemp, Error, TEXT("FINISHED BLACK HOLE"));

	FTimerHandle Growth2Handle;
	GetWorldTimerManager().SetTimer(Growth2Handle, this, &AC_BlackHole::PlayGrowth2, 3.0f, false);
}

void AC_BlackHole::PlayGrowth2()
{
	FinalScale = GetActorScale3D();

	FinalScale2 = GetActorScale3D() * Scale2;

	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		PlayerController->ClientPlayCameraShake(BlackHoleCameraShake);
	}

	Growth2Timeline->Play();
}

void AC_BlackHole::Growth2TimelineFloatReturn(float Value)
{
	SetActorScale3D(FVector(FMath::Lerp(FinalScale, FinalScale2, Value)));
}