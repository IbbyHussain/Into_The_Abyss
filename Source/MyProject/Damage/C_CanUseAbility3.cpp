#include "C_CanUseAbility3.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UC_CanUseAbility3::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if(PlayerCharacter)
    {
        PlayerCharacter->bCanUseAbility3 = false;
    }
}