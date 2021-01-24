// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftHandMagic.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALeftHandMagic::ALeftHandMagic()
{
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Effect"));
	FireEffect->SetupAttachment(Effect);

	IceEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ice Effect"));
	IceEffect->SetupAttachment(Effect);

	VoidEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Void Effect"));
	VoidEffect->SetupAttachment(Effect);

	AirEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Air Effect"));
	AirEffect->SetupAttachment(Effect);

	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(true);
}

void ALeftHandMagic::ShowDefaultEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(true);
}

void ALeftHandMagic::ShowFireEffect()
{
	FireEffect->SetVisibility(true);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(false);
}

void ALeftHandMagic::ShowIceEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(true);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(false);
}

void ALeftHandMagic::ShowVoidEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(true);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(false);
}

void ALeftHandMagic::ShowAirEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(true);
	Effect->SetVisibility(false);
}

void ALeftHandMagic::Visible()
{
	Effect->SetVisibility(true);
}

void ALeftHandMagic::InVisible()
{
	Effect->SetVisibility(false);
}

