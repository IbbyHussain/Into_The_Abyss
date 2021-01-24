// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnableAbility3Notify.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UC_EnableAbility3Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (PlayerCharacter)
    {
        PlayerCharacter->bCanUseAbility3 = true;
    }
}
