#include "C_EnableRagdollNotify.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"

void UC_EnableRagdollNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	
}
void UC_EnableRagdollNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	class AC_PlayerCharacter* Character = Cast <AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp, 0));

	// Applies damage via player character function 
	if (Character)
	{
		Character->Rag(MeshComp);
	}
}
void UC_EnableRagdollNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	class AC_PlayerCharacter* Character = Cast <AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp, 0));

	Character->ResetAttackVar();
}