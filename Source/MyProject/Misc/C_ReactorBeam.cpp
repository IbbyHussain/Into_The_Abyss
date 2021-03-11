
#include "C_ReactorBeam.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraSystem.h"

#include "NiagaraFunctionLibrary.h"

AC_ReactorBeam::AC_ReactorBeam()
{
	PrimaryActorTick.bCanEverTick = true;

	BeamComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Beam"));

	MaxBeamRange = 500.0f;

	MinBeamRange = -500.0f;

	LightningFrequency = 0.5f;
}

void AC_ReactorBeam::BeginPlay()
{
	Super::BeginPlay();

	BeamComp->SetNiagaraVariableVec3(FString("Target"), EndActor->GetActorLocation());

	// Gives impression that beam has no tangents 
	//BeamComp->SetNiagaraVariableVec3(FString("TangentStart"), TangentActor->GetActorLocation());
	//BeamComp->SetNiagaraVariableVec3(FString("TangentEnd"), TangentActor->GetActorLocation());

	SpawnEffects();

	BeginCorruption();
}

// starts corruption sequence
void AC_ReactorBeam::BeginCorruption()
{
	// Adds tangent curves to the beam
	BeamComp->SetNiagaraVariableVec3(FString("TangentStart"), FVector(1.0f));
	BeamComp->SetNiagaraVariableVec3(FString("TangentEnd"), FVector(1.0f));

	GetWorldTimerManager().SetTimer(ChangeTargetLocationHandle, this, &AC_ReactorBeam::BecomeCorrupted, LightningFrequency, true);
}

void AC_ReactorBeam::BecomeCorrupted()
{
	// sets the target to random points in world
	BeamComp->SetNiagaraVariableVec3(FString("Target"), FVector(UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange), UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange),
		UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange)));
}

void AC_ReactorBeam::SpawnEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SparksEffect, GetActorLocation());
}
