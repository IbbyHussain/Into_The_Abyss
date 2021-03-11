
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
}

void AC_ReactorBeam::BeginPlay()
{
	Super::BeginPlay();

	SpawnEffects();

	BeamComp->SetNiagaraVariableVec3(FString("Target"), TargetActor->GetActorLocation());

	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), color * UKismetMathLibrary::HSVToRGB(0.0f, 0.0f, 1000.0f, 1.0f));
}

void AC_ReactorBeam::BeginCorruption()
{
	GetWorldTimerManager().SetTimer(ChangeTargetLocationHandle, this, &AC_ReactorBeam::BecomeCorrupted, 0.5f, true);
}

void AC_ReactorBeam::BecomeCorrupted()
{
	BeamComp->SetNiagaraVariableVec3(FString("Target"), FVector(UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange), UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange),
		UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange)));
}

void AC_ReactorBeam::SpawnEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SparksEffect, GetActorLocation());
}
