// Fill out your copyright notice in the Description page of Project Settings.


#include "C_WarningLight.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"

AC_WarningLight::AC_WarningLight()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	PointLight->SetupAttachment(MeshComp);
	PointLight->LightColor = FColor(0, 255, 0);
	PointLight->SetMobility(EComponentMobility::Stationary);
}

void AC_WarningLight::BeginPlay()
{
	Super::BeginPlay();
	PointLight->SetLightColor(FLinearColor::Green);
}

void AC_WarningLight::StartPulse()
{
	//PointLight->SetLightColor(FLinearColor::Red); can be here if player doesnt see lights immediately 
	MatInst = UMaterialInstanceDynamic::Create(WarningLightGlow, this);
	MeshComp->SetMaterial(1, MatInst);
	GetWorldTimerManager().SetTimer(PulseHandle, this, &AC_WarningLight::Pulse, 2.0, true);
}

void AC_WarningLight::Pulse()
{
	PointLight->SetLightColor(FLinearColor::Red);
	MatInst->SetScalarParameterValue("LastTimeDamagedTaken", GetWorld()->TimeSeconds);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WarningLightSound, GetActorLocation());
}

