// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MeleeAIDamageNotify.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "MyProject/AI/C_BaseAI.h"

void UC_MeleeAIDamageNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	BaseMeleeAI = Cast<AC_MeleeAI>(MeshComp->GetAnimInstance()->TryGetPawnOwner());

	// W	ill multipley damage by 5 each attack
	if (BaseMeleeAI && BaseMeleeAI->bIsBossAI)
	{
		Damage *= 5.0;
	}
}

void UC_MeleeAIDamageNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if(BaseMeleeAI)
	{
		BaseMeleeAI->MeleeAIDamage(MeshComp, Damage);
	}
}

void UC_MeleeAIDamageNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(BaseMeleeAI)
	{
		BaseMeleeAI->bCanAttack = true;

		// Sets attack back to normal
		if(BaseMeleeAI->bIsBossAI)
		{
			Damage /= 5.0;
		}
	}
}
