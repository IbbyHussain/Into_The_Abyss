// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseCustomisedAI.h"
#include "MyProject/Weapons/MeleeWeapons/C_BaseSkeletalMeleeWeapon.h"

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
}

// AI Customisation 
AActor* AC_BaseCustomisedAI::SpawnWeapon(TSubclassOf<AActor> WeaponClass, TSubclassOf<AActor> SickleClass)
{
	//Spawns a random weapon (random weapon logic is in bp)

	Weapon = SpawnItem(Melee.RHSocket, Melee.MeleeWeapon, false, WeaponClass);

	// If the random weapon is a Sickle will adjust its location and attach to a different socket due to its size 
	if (Weapon->GetClass() == SickleClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Sickle"));

		Weapon->SetActorTransform(GetMesh()->GetSocketTransform(Melee.SickleSocket));
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Melee.SickleSocket);

		return Weapon;
	}

	// If the random weapon is a not a sickle will attach it to the default socket
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Other"));

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

AActor* AC_BaseCustomisedAI::SpawnBackpack(TSubclassOf<AC_SkeletalMeshActor> BackpackClass)
{
	// Only if a class is selected will one spawn allows nothing to spawn as well
	if (BackpackClass)
	{
		AActor* BackpackPTR = SpawnItem(Backpack.BackSocket, Backpack.SKMesh, true, BackpackClass);

		return BackpackPTR;
	}

	return NULL;
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