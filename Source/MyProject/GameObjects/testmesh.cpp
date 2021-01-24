// Fill out your copyright notice in the Description page of Project Settings.


#include "testmesh.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"

Atestmesh::Atestmesh()
{
	Pitch = 0.0f;
	Yaw = 0.0f;
	Roll = 0.0f;

	Timeline1 = CreateDefaultSubobject<UTimelineComponent>(TEXT("SlideTimeline"));
	Timeline1InterpFunction.BindUFunction(this, FName("Timeline1FloatReturn"));

	Timeline2 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Slide2Timeline"));
	Timeline2InterpFunction.BindUFunction(this, FName("Timeline2FloatReturn"));

	Timeline3 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Slide3Timeline"));
	Timeline3InterpFunction.BindUFunction(this, FName("Timeline3FloatReturn"));

	Timeline4 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Slide4Timeline"));
	Timeline4InterpFunction.BindUFunction(this, FName("Timeline4FloatReturn"));

	Timeline1Value = 0.0f;
	Timeline2Value = 0.0f;
	Timeline3Value = 0.0f;

}

void Atestmesh::BeginPlay()
{
	Super::BeginPlay();

	/*FQuat QuatRotation = FQuat(FRotator(Pitch, Yaw, Roll));

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);*/

	if(FCurve)
	{
		UE_LOG(LogTemp, Log, TEXT("!!!"));
		Timeline1->AddInterpFloat(FCurve, Timeline1InterpFunction, FName("aplah"));
		Timeline1->SetLooping(false);

		Timeline2->AddInterpFloat(FCurve, Timeline2InterpFunction, FName("Bravo"));
		Timeline2->SetLooping(false);

		Timeline3->AddInterpFloat(FCurve, Timeline3InterpFunction, FName("charlie"));
		Timeline3->SetLooping(false);

		Timeline4->AddInterpFloat(FCurve, Timeline4InterpFunction, FName("delta"));
		Timeline4->SetLooping(false);
	}

	Timeline1->Play();
	GetWorldTimerManager().SetTimer(RotateHandle, this, &Atestmesh::Reset, 4.0f, false);
}

void Atestmesh::Timeline1FloatReturn(float Value)
{
	float r = MeshComp->GetRelativeRotation().Roll;
	float y = MeshComp->GetRelativeRotation().Pitch;
	float z = MeshComp->GetRelativeRotation().Yaw;
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value, 0.0f));

	Timeline1Value = Value;
}



void Atestmesh::Timeline2FloatReturn(float Value)
{
	float r = MeshComp->GetRelativeRotation().Roll;
	float y = MeshComp->GetRelativeRotation().Pitch;
	float z = MeshComp->GetRelativeRotation().Yaw;
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value + Timeline1Value, 0.0f));

	Timeline2Value = Value;
}



void Atestmesh::Timeline3FloatReturn(float Value)
{
	float r = MeshComp->GetRelativeRotation().Roll;
	float y = MeshComp->GetRelativeRotation().Pitch;
	float z = MeshComp->GetRelativeRotation().Yaw;
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value + Timeline1Value + Timeline2Value, 0.0f));

	Timeline3Value = Value;
}



void Atestmesh::Timeline4FloatReturn(float Value)
{
	float r = MeshComp->GetRelativeRotation().Roll;
	float y = MeshComp->GetRelativeRotation().Pitch;
	float z = MeshComp->GetRelativeRotation().Yaw;
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value + Timeline1Value + Timeline2Value + Timeline3Value, 0.0f));
}

void Atestmesh::Reset()
{
	Timeline2->Play();
	GetWorldTimerManager().ClearTimer(RotateHandle);
	GetWorldTimerManager().SetTimer(RotateHandle, this, &Atestmesh::Reset2, 4.0f, false);
}

void Atestmesh::Reset2()
{
	Timeline3->Play();
	GetWorldTimerManager().ClearTimer(RotateHandle);
	GetWorldTimerManager().SetTimer(RotateHandle, this, &Atestmesh::Reset3, 4.0f, false);
}

void Atestmesh::Reset3()
{
	Timeline4->Play();
	GetWorldTimerManager().ClearTimer(RotateHandle);
}