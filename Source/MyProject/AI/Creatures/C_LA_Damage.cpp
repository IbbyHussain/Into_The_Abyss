// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LA_Damage.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/Creatures/C_LostAdventurer.h"

void UC_LA_Damage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	LAAI = Cast<AC_LostAdventurer>(MeshComp->GetAnimInstance()->TryGetPawnOwner());

	if(LAAI && LAAI->bIsBossAI)
	{
		Damage *= BossDamageMultiplier;
	}
}

void UC_LA_Damage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (LAAI)
	{
		LAAI->Attack(MeshComp, Damage, Start, End);
	}
}

void UC_LA_Damage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (LAAI)
	{
		LAAI->bLAcanAttack = true;

		if (LAAI->bIsBossAI)
		{
			Damage /= BossDamageMultiplier;
		}
	}
}
