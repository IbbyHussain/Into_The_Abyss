// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ArcherAI.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"

#include "MyProject/Weapons/Crossbow/C_SteelBolt.h"
#include "MyProject/Weapons/Crossbow/C_DummyBolt.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "Kismet/GameplayStatics.h"

void AC_ArcherAI::BeginPlay()
{
	Super::BeginPlay();

	Crossbow = Cast<AC_Crossbow>(Weapon);

	Crossbow->MeshComp->PlayAnimation(CrossbowReloadMontage, false);
	Crossbow->SpawnDummybolt(Crossbow->CrossbowboltSocket, SteelDummyBolt);
}

void AC_ArcherAI::ChangeAIColour()
{
	Super::ChangeAIColour();

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 0);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 2);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 7);
}

void AC_ArcherAI::BasicAttack()
{
	Super::BasicAttack();

	if(Crossbow)
	{
		PlayAnimMontage(AttackMontage, 1.0f);
		
		Crossbow->SpawnBoltAI(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CrossbowFireSound, GetActorLocation());

		Crossbow->ReloadCrossbow();
	}
}