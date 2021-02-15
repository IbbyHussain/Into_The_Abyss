// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseCustomisedAI.h"
#include "MyProject/Weapons/MeleeWeapons/C_BaseSkeletalMeleeWeapon.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_DummyBolt.h"

AC_BaseCustomisedAI::AC_BaseCustomisedAI()
{
	
}

void AC_BaseCustomisedAI::BeginPlay()
{
	Super::BeginPlay();

	// Create the dynamic materials using the interface materials
	SkinColourMaterial.DynamicLightSkinColour = UMaterialInstanceDynamic::Create(SkinColourMaterial.SkinMaterialInterfaceArray[0], this); //LightSkinColour
	SkinColourMaterial.DynamicMediumSkinColour = UMaterialInstanceDynamic::Create(SkinColourMaterial.SkinMaterialInterfaceArray[1], this);
	SkinColourMaterial.DynamicDarkSkinColour = UMaterialInstanceDynamic::Create(SkinColourMaterial.SkinMaterialInterfaceArray[2], this);

	// Initialse the dyankic material array with the created dynamic materials
	SkinColourMaterial.SkinMaterialArray = { SkinColourMaterial.DynamicLightSkinColour, SkinColourMaterial.DynamicMediumSkinColour, SkinColourMaterial.DynamicDarkSkinColour };

	ClothingColourMaterial.DynamicRedColour = UMaterialInstanceDynamic::Create(ClothingColourMaterial.ClothingMaterialInterfaceArray[0], this);
	ClothingColourMaterial.DynamicGreenColour = UMaterialInstanceDynamic::Create(ClothingColourMaterial.ClothingMaterialInterfaceArray[1], this);
	ClothingColourMaterial.DynamicBlueColour = UMaterialInstanceDynamic::Create(ClothingColourMaterial.ClothingMaterialInterfaceArray[2], this);

	ClothingColourMaterial.ClothingMaterialArray = { ClothingColourMaterial.DynamicRedColour, ClothingColourMaterial.DynamicGreenColour, ClothingColourMaterial.DynamicBlueColour };

	ChangeAIColour();

	// Add the assigned materials to a new array
	for (int i = 0; i < GetMesh()->GetMaterials().Num(); i++) 
	{
		CustomisedMaterials.Add(GetMesh()->GetMaterials()[i]);
	}


}

// AI Customisation 
AActor* AC_BaseCustomisedAI::SpawnWeapon(TSubclassOf<AActor> WeaponClass, TSubclassOf<AActor> SickleClass)
{
	//Spawns a random weapon (random weapon logic is in bp)

	Weapon = SpawnItem(Melee.RHSocket, Melee.MeleeWeapon, false, WeaponClass);

	// If the random weapon is a Sickle will adjust its location and attach to a different socket due to its size 
	if (Weapon->GetClass() == SickleClass)
	{

		Weapon->SetActorTransform(GetMesh()->GetSocketTransform(Melee.SickleSocket));
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Melee.SickleSocket);

		return Weapon;
	}

	// If the random weapon is a not a sickle will attach it to the default socket
	else
	{

		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Melee.RHSocket);

		return Weapon;
	}

	return Weapon;
}

// Spawns a two handed weapon
AActor* AC_BaseCustomisedAI::SpawnTwoHandedWeapon(TSubclassOf<AActor> WeaponClass, TSubclassOf<AActor> SwordClass)
{
	//Spawns a random weapon (random weapon logic is in bp)
	Weapon = SpawnItem(Melee.TwoHandedSocket, Melee.MeleeWeapon, false, WeaponClass);

	// If the random weapon is a sword will adjust its location and attach to a different socket due to its size 
	if (Weapon->GetClass() == SwordClass)
	{
		Weapon->SetActorTransform(GetMesh()->GetSocketTransform(Melee.TwoHandedSwordSocket));
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Melee.TwoHandedSwordSocket);

		return Weapon;
	}

	// If the random weapon is a not a sword will attach it to the default socket
	else
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Melee.TwoHandedSocket);

		return Weapon;
	}

	return Weapon;
}

AActor* AC_BaseCustomisedAI::SpawnCrossbow(TSubclassOf<AActor> WeaponClass)
{
	//Spawns a random weapon (random weapon logic is in bp)
	Weapon = SpawnItem(Melee.CrossbowSocket, Melee.MeleeWeapon, false, WeaponClass);

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Melee.CrossbowSocket);

	return Weapon;
}

AActor* AC_BaseCustomisedAI::SpawnBackpack(TSubclassOf<AC_SkeletalMeshActor> BackpackClass)
{
	// Only if a class is selected will one spawn allows nothing to spawn as well
	if (BackpackClass)
	{
		BackpackPTR = SpawnItem(Backpack.BackSocket, Backpack.SKMesh, true, BackpackClass);

		return BackpackPTR;
	}

	return NULL;
}

void AC_BaseCustomisedAI::ResetMaterials()
{
	Super::ResetMaterials();

	// Reset Materials to default
	for (int i = 0; i < GetMesh()->GetMaterials().Num(); i++)
	{
		GetMesh()->SetMaterial(i, CustomisedMaterials[i]);
	}
}

void AC_BaseCustomisedAI::ChangeAIColour()
{
	// Old way use for NEA
	/*int a = FMath::RandRange(0, 2);
	int b = FMath::RandRange(0, 2);
	UE_LOG(LogTemp, Log, TEXT("Random int is: %d"), a);

	// Set the skin colour to a random colour
	GetMesh()->SetMaterial(0, SkinColourMaterial.SkinMaterialArray[a]);

	// Set the torso and hat colour to a random colour / a is a saved value so need to generate a new number
	// otherwise the hat and torso will have same colour
	GetMesh()->SetMaterial(1, ClothingColourMaterial.ClothingMaterialArray[a]);
	GetMesh()->SetMaterial(2, ClothingColourMaterial.ClothingMaterialArray[b]);*/

}

void AC_BaseCustomisedAI::GetDefaultWeaponMaterials()
{
	// Get materials for melee weapon
	AC_BaseSkeletalMeleeWeapon* AIWeapon = Cast<AC_BaseSkeletalMeleeWeapon>(Weapon);

	if(AIWeapon)
	{
		for (int i = 0; i < AIWeapon->MeshComp->GetMaterials().Num(); i++) // Need to get the materials that have been assigned
		{
			DefaultWeaponMaterials.Add(AIWeapon->MeshComp->GetMaterials()[i]);
		}
	}

	// Get materials for crossbows
	AC_Crossbow* Crossbow = Cast<AC_Crossbow>(Weapon);

	if(Crossbow)
	{
		for (int i = 0; i < Crossbow->MeshComp->GetMaterials().Num(); i++)
		{
			DefaultWeaponMaterials.Add(Crossbow->MeshComp->GetMaterials()[i]);
		}
	}
}

void AC_BaseCustomisedAI::GetDefaultBackpackMaterials()
{
	AC_SkeletalMeshActor* AIBackpack = Cast<AC_SkeletalMeshActor>(BackpackPTR);

	if (AIBackpack)
	{
		for (int i = 0; i < AIBackpack->MeshComp->GetMaterials().Num(); i++) // Need to get the materials that have been assigned
		{
			DefaultBackpackMaterials.Add(AIBackpack->MeshComp->GetMaterials()[i]);
		}
	}
}

void AC_BaseCustomisedAI::BecomeFrozen()
{
	Super::BecomeFrozen();

	WeaponBecomeFrozen();

	BackpackBecomeFrozen();
}

void AC_BaseCustomisedAI::BecomeUnFrozen()
{
	Super::BecomeUnFrozen();

	WeaponBecomeUnFrozen();

	BackpackBecomeUnFrozen();
}

void AC_BaseCustomisedAI::WeaponBecomeFrozen()
{
	AC_BaseSkeletalMeleeWeapon* AIWeapon = Cast<AC_BaseSkeletalMeleeWeapon>(Weapon);

	if (AIWeapon)
	{
		for (int i = 0; i < AIWeapon->MeshComp->GetMaterials().Num(); i++)
		{
			AIWeapon->MeshComp->SetMaterial(i, FrozenMaterial);
		}
	}

	// Get materials for crossbows
	AC_Crossbow* Crossbow = Cast<AC_Crossbow>(Weapon);

	if (Crossbow)
	{
		for (int i = 0; i < Crossbow->MeshComp->GetMaterials().Num(); i++)
		{
			Crossbow->MeshComp->SetMaterial(i, FrozenMaterial);
			Crossbow->DummyBolt->SetActorHiddenInGame(true);
		}
	}
}

void AC_BaseCustomisedAI::WeaponBecomeUnFrozen()
{
	AC_BaseSkeletalMeleeWeapon* AIWeapon = Cast<AC_BaseSkeletalMeleeWeapon>(Weapon);

	if(AIWeapon)
	{
		for (int i = 0; i < AIWeapon->MeshComp->GetMaterials().Num(); i++)
		{
			AIWeapon->MeshComp->SetMaterial(i, DefaultWeaponMaterials[i]);
		}
	}

	// Get materials for crossbows
	AC_Crossbow* Crossbow = Cast<AC_Crossbow>(Weapon);

	if (Crossbow)
	{
		for (int i = 0; i < Crossbow->MeshComp->GetMaterials().Num(); i++)
		{
			Crossbow->MeshComp->SetMaterial(i, DefaultWeaponMaterials[i]);
			Crossbow->DummyBolt->SetActorHiddenInGame(false);
		}
	}
}

void AC_BaseCustomisedAI::BackpackBecomeFrozen()
{
	AC_SkeletalMeshActor* AIBackpack = Cast<AC_SkeletalMeshActor>(BackpackPTR);

	if (AIBackpack)
	{
		for (int i = 0; i < AIBackpack->MeshComp->GetMaterials().Num(); i++) 
		{
			AIBackpack->MeshComp->SetMaterial(i, FrozenMaterial);
		}
	}
}

void AC_BaseCustomisedAI::BackpackBecomeUnFrozen()
{
	AC_SkeletalMeshActor* AIBackpack = Cast<AC_SkeletalMeshActor>(BackpackPTR);

	if (AIBackpack)
	{
		for (int i = 0; i < AIBackpack->MeshComp->GetMaterials().Num(); i++) 
		{
			AIBackpack->MeshComp->SetMaterial(i, DefaultBackpackMaterials[i]);
		}
	}
}
