// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MeleeAI.h"

AC_MeleeAI::AC_MeleeAI()
{
	// change when savage class is created
	TypeOfAI = ETypeOfAI::SAVAGE;
}

void AC_MeleeAI::BeginPlay()
{
	Super::BeginPlay();
}

void AC_MeleeAI::BasicAttack()
{
	PlayAnimMontage(BasicAttackMontage, 1.0f);
}