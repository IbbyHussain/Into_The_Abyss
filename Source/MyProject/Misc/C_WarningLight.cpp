// Fill out your copyright notice in the Description page of Project Settings.


#include "C_WarningLight.h"
#include "Kismet/GameplayStatics.h"

AC_WarningLight::AC_WarningLight()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AC_WarningLight::BeginPlay()
{
	Super::BeginPlay();

	MatInst = UMaterialInstanceDynamic::Create(WarningLightGlow, this);

	//StartPulse();
}

void AC_WarningLight::StartPulse()
{
	MeshComp->SetMaterial(1, MatInst);
	GetWorldTimerManager().SetTimer(PulseHandle, this, &AC_WarningLight::Pulse, 1.0, true);
}

void AC_WarningLight::Pulse()
{
	MatInst->SetScalarParameterValue("LastTimeDamagedTaken", GetWorld()->TimeSeconds);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WarningLightSound, GetActorLocation());
}

