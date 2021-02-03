// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerController.h"

AC_PlayerController::AC_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TeamId = FGenericTeamId(10);
}

FGenericTeamId AC_PlayerController::GetGenericTeamId() const
{
	return TeamId;
}
