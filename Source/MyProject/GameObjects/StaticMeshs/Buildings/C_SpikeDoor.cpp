// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SpikeDoor.h"
#include "Kismet/GameplayStatics.h"

AC_SpikeDoor::AC_SpikeDoor()
{
	SpikeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SpikeTimeline"));
	SpikeInterpFunction.BindUFunction(this, FName("SpikeTimelineFloatReturn"));

	DefaultMeshHeight = MeshComp->GetRelativeLocation().Z;
	SwimMeshHeight = DefaultMeshHeight / 0.1f;
}

void AC_SpikeDoor::BeginPlay()
{
	Super::BeginPlay();

	float Z = GetActorLocation().Z;
	UE_LOG(LogTemp, Log, TEXT("%f"), Z)

	if(FSpikeCurve)
	{
		SpikeTimeline->AddInterpFloat(FSpikeCurve, SpikeInterpFunction, FName("Alpha"));
		SpikeTimeline->SetLooping(false);
	}
}

void AC_SpikeDoor::SpikeTimelineFloatReturn(float Value)
{
	float X = GetActorLocation().X;
	float Y = GetActorLocation().Y;
	float Z = GetActorLocation().Z;
	//SetActorLocation(FVector(X, Y, (FMath::Lerp(Z, 275.0f, Value))));
	SetActorLocation(FMath::Lerp(GetActorLocation(), TargetLocation, Value));
}

void AC_SpikeDoor::PlayOpenDoorAnimation()
{
	SpikeTimeline->PlayFromStart();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpenSound, GetActorLocation());
}