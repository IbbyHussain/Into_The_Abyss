// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "C_PeasantAI.generated.h"

UCLASS()
class MYPROJECT_API AC_PeasantAI : public AC_MeleeAI
{
	GENERATED_BODY()

	AC_PeasantAI();

private:

	virtual void ChangeAIColour() override;
	
};
