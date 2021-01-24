// Fill out your copyright notice in the Description page of Project Settings.


#include "C_RightHandMagic.h"
#include "Particles/ParticleSystemComponent.h"


AC_RightHandMagic::AC_RightHandMagic()
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

void AC_RightHandMagic::ShowDefaultEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(true);
}

void AC_RightHandMagic::ShowFireEffect()
{
	FireEffect->SetVisibility(true);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(false);
}

void AC_RightHandMagic::ShowIceEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(true);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(false);
}

void AC_RightHandMagic::ShowVoidEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(true);
	AirEffect->SetVisibility(false);
	Effect->SetVisibility(false);
}

void AC_RightHandMagic::ShowAirEffect()
{
	FireEffect->SetVisibility(false);
	IceEffect->SetVisibility(false);
	VoidEffect->SetVisibility(false);
	AirEffect->SetVisibility(true);
	Effect->SetVisibility(false);
}


void AC_RightHandMagic::Visible()
{
	Effect->SetVisibility(true);
}

void AC_RightHandMagic::InVisible()
{
	Effect->SetVisibility(false);
}