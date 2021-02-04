// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_UpdateCapsuleNotify.generated.h"

UCLASS()
class MYPROJECT_API UC_UpdateCapsuleNotify : public UAnimNotifyState
{
	GENERATED_BODY()

	UC_UpdateCapsuleNotify();

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	
};
