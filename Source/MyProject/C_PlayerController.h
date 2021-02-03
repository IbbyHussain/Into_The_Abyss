// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "C_PlayerController.generated.h"

UCLASS()
class MYPROJECT_API AC_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AC_PlayerController();

private:
	// Implement The Generic Team Interface 
	FGenericTeamId TeamId;
	FGenericTeamId GetGenericTeamId() const;
	
};
