#include "C_MeleeDamageNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/CollisionProfile.h"
#include "MyProject\MyProject.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"

void UC_MeleeDamageNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

}
void UC_MeleeDamageNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	class AC_PlayerCharacter* Character = Cast <AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp, 0));

	// Applies damage via player character function 
	if(Character)
	{
		Character->MeleeAttackDamage(MeshComp, Damage, DamageOverTime);
	}
}
void UC_MeleeDamageNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	class AC_PlayerCharacter* Character = Cast <AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(MeshComp, 0));

	Character->ResetAttackVar();
}