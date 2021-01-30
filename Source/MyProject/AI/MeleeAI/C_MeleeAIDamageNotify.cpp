// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MeleeAIDamageNotify.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"

void UC_MeleeAIDamageNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

}

void UC_MeleeAIDamageNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	AC_MeleeAI* BaseMeleeAI = Cast<AC_MeleeAI>(MeshComp->GetAnimInstance()->TryGetPawnOwner());

	if(BaseMeleeAI)
	{

		BaseMeleeAI->MeleeAIDamage(MeshComp, 10.0f);
	}
}