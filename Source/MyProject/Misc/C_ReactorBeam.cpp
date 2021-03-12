
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

	SpawnEffects();

	// Sets the beams target (where it will strike).
	BeamComp->SetNiagaraVariableVec3(FString("Target"), TargetActor->GetActorLocation());

	// Sets the default beam colour to a colour variable in editor. Also gives it some emissive value (HSV).
	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), color * UKismetMathLibrary::HSVToRGB(0.0f, 0.0f, 1000.0f, 1.0f));
}

void AC_ReactorBeam::BeginCorruption()
{
	GetWorldTimerManager().SetTimer(ChangeTargetLocationHandle, this, &AC_ReactorBeam::BecomeCorrupted, LightningFrequency, true);
}

void AC_ReactorBeam::BecomeCorrupted()
{
	// Beams will strike random areas
	BeamComp->SetNiagaraVariableVec3(FString("Target"), FVector(UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange), UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange),
		UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange)));

	// Sets beams to black
	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), FLinearColor::Black);
}

void AC_ReactorBeam::SpawnEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SparksEffect, GetActorLocation());
}
