
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

	// Timeline creation and binding
	ColourChangeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Colour change Timeline"));
	ColourChangeInterpFunction.BindUFunction(this, FName("ColourChangeTimelineFloatReturn"));
}

void AC_ReactorBeam::BeginPlay()
{
	Super::BeginPlay();

	BeamComp->SetVisibility(false);

	// Sets the beams target (where it will strike).
	if(TargetActor)
	{
		BeamComp->SetNiagaraVariableVec3(FString("Target"), TargetActor->GetActorLocation());
	}

	// Sets the default beam colour to a colour variable in editor. Also gives it some emissive value (HSV).
	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), color * UKismetMathLibrary::HSVToRGB(0.0f, 0.0f, 1000.0f, 1.0f));

	// Timeline setup
	if(FColourChangeCurve)
	{
		ColourChangeTimeline->AddInterpFloat(FColourChangeCurve, ColourChangeInterpFunction, FName("Alpha"));
		ColourChangeTimeline->SetLooping(false);
	}

	//BeginCorruption();
}

void AC_ReactorBeam::BeginCorruption()
{
	// Start change colour timeline
	ColourChangeTimeline->Play();

	GetWorldTimerManager().SetTimer(ChangeTargetLocationHandle, this, &AC_ReactorBeam::BecomeCorrupted, LightningFrequency, true, 7.0f);
}

void AC_ReactorBeam::BecomeCorrupted()
{
	// Beams will strike random areas
	BeamComp->SetNiagaraVariableVec3(FString("Target"), FVector(UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange), UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange),
		UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange)));
}

void AC_ReactorBeam::SpawnEffects()
{
	UNiagaraComponent* SparksComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SparksEffect, GetActorLocation());
	SparksComp->SetNiagaraVariableLinearColor(FString("Color"), color * UKismetMathLibrary::HSVToRGB(0.0f, 0.0f, 1000.0f, 1.0f));
}

void AC_ReactorBeam::ColourChangeTimelineFloatReturn(float Alpha)
{
	// Smoothly transitions from original colour to black
	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), UKismetMathLibrary::LinearColorLerp(color * UKismetMathLibrary::HSVToRGB(0.0f, 0.0f, 1000.0f, 1.0f), FLinearColor::Black, Alpha));
}

void AC_ReactorBeam::BecomeVisible()
{
	BeamComp->SetVisibility(true);
	SpawnEffects();
}

void AC_ReactorBeam::MinorBeamSetup()
{
	GetWorldTimerManager().SetTimer(ChangeTargetLocationHandle, this, &AC_ReactorBeam::MinorBeamBecomeCorrupted, LightningFrequency, true, 7.0f);
	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), FLinearColor::Black);
}

void AC_ReactorBeam::MinorBeamBecomeCorrupted()
{
	BeamComp->SetNiagaraVariableLinearColor(FString("Color"), FLinearColor::Black);
	BeamComp->SetVisibility(true);

	// Beams will strike random areas
	BeamComp->SetNiagaraVariableVec3(FString("Target"), FVector(UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange), UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange),
		UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange)));
}