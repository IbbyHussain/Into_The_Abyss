
#include "C_ReactorBeam.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	GetWorldTimerManager().SetTimer(ChangeTargetLocationHandle, this, &AC_ReactorBeam::BecomeCorrupted, 0.5f, true);
	
}

void AC_ReactorBeam::BecomeCorrupted()
{
	BeamComp->SetNiagaraVariableVec3(FString("Target"), FVector(UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange), UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange),
		UKismetMathLibrary::RandomFloatInRange(MinBeamRange, MaxBeamRange)));
}
