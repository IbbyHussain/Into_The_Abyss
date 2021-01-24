// Fill out your copyright notice in the Description page of Project Settings.


#include "C_FloatingActor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"

// Sets default values
AC_FloatingActor::AC_FloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));

	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

	ZOffset = 50.0f;

}

// Called when the game starts or when spawned
void AC_FloatingActor::BeginPlay()
{
	Super::BeginPlay();

	if(FCurve)
	{
		MyTimeline->AddInterpFloat(FCurve, InterpFunction, FName("Alpha"));
		MyTimeline->SetTimelineFinishedFunc(TimelineFinished);

		StartLocation = GetActorLocation();

		EndLocation = FVector(StartLocation.X, StartLocation.Y, StartLocation.Z + ZOffset);

		MyTimeline->SetLooping(false);
		MyTimeline->SetIgnoreTimeDilation(true);

		MyTimeline->Play();
	}
}

// Called every frame
void AC_FloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_FloatingActor::TimelineFloatReturn(float Value)
{
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value));
}

void AC_FloatingActor::OnTimelineFinished()
{
	if(MyTimeline->GetPlaybackPosition() == 0.0f)
	{
		GLog->Log("Play");
		MyTimeline->Play();
	}
}