// Fill out your copyright notice in the Description page of Project Settings.


#include "C_UpdateCapsuleLocationNotify.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"

void UC_UpdateCapsuleLocationNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AC_MeleeAI* MeleeAI = Cast<AC_MeleeAI>(MeshComp->GetAnimInstance()->TryGetPawnOwner());
	if (MeleeAI)
	{
		MeleeAI->UpdateCapsuleForAnimations();
		//MeleeAI->GetMesh()->GetAnimInstance()->Montage_Stop(0.1, Montageref);
	}
}