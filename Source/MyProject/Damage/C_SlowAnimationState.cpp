
#include "C_SlowAnimationState.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"

void UC_SlowAnimationState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	class AC_PlayerCharacter* Character = Cast <AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp, 0));

	if(Character)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Character->SS.DefaultAttack1, 0.75f);
		Character->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Character->SS.DefaultAttack2, 0.5f);
		Character->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Character->SS.DefaultAttack3, 0.75f);
	}

}

void UC_SlowAnimationState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UC_SlowAnimationState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	class AC_PlayerCharacter* Character = Cast <AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp, 0));
	if (Character)
	{
		Character->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Character->SS.DefaultAttack1, 1.0f);
		Character->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Character->SS.DefaultAttack2, 1.0f);
		Character->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Character->SS.DefaultAttack3, 1.0f);
	}
}
