// Fill out your copyright notice in the Description page of Project Settings.


#include "C_UpdateCapsuleNotify.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"

UC_UpdateCapsuleNotify::UC_UpdateCapsuleNotify()
{

}

void UC_UpdateCapsuleNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	AC_MeleeAI* MeleeAI = Cast<AC_MeleeAI>(MeshComp->GetAnimInstance()->TryGetPawnOwner());
	if(MeleeAI)
	{
		MeleeAI->UpdateCapsuleForAnimations();
	}
}
