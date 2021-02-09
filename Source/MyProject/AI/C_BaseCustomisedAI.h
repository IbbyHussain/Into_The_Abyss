#pragma once
#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseAI.h"
#include "C_BaseCustomisedAI.generated.h"


class AC_SkeletalMeshActor;
class AC_BaseSkeletalMeleeWeapon;

// Melee Struct
USTRUCT(BlueprintType)
struct FMelee
{
	GENERATED_BODY()

	AC_BaseSkeletalMeleeWeapon* MeleeWeapon;

	FName RHSocket;

	FName SickleSocket;

	FName TwoHandedSocket;

	FName TwoHandedSwordSocket;

	//Constructor
	FMelee()
	{
		RHSocket = ("RightHandSocket");

		SickleSocket = ("SickleSocket");

		TwoHandedSocket = ("TwoHandedSocket");

		TwoHandedSwordSocket = ("TwoHandedSocketSword");
	}
};

USTRUCT(BlueprintType)
struct FBackpack
{
	GENERATED_BODY()

	FName BackSocket;

	AC_SkeletalMeshActor* SKMesh;

	TArray<AC_SkeletalMeshActor*> SKMeshArray;

	FBackpack()
	{
		BackSocket = ("BackpackSocket");
	}
};

// Skin Colour Material Struct
USTRUCT(BlueprintType)
struct FSkinColourMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	TArray<UMaterialInterface*> SkinMaterialInterfaceArray;

	TArray<UMaterialInstanceDynamic*> SkinMaterialArray;

	// Skin colour Dynamic material pointers
	UMaterialInstanceDynamic* DynamicLightSkinColour;
	UMaterialInstanceDynamic* DynamicMediumSkinColour;
	UMaterialInstanceDynamic* DynamicDarkSkinColour;

	//Constructor
	FSkinColourMaterial()
	{

	}
};

// Clothing Colour Material Struct
USTRUCT(BlueprintType)
struct FClothingColourMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	TArray<UMaterialInterface*> ClothingMaterialInterfaceArray;

	TArray<UMaterialInstanceDynamic*> ClothingMaterialArray;

	// Hat colour Dynamic material pointers
	UMaterialInstanceDynamic* DynamicRedColour;
	UMaterialInstanceDynamic* DynamicGreenColour;
	UMaterialInstanceDynamic* DynamicBlueColour;

	//Constructor
	FClothingColourMaterial()
	{

	}
};

UCLASS()
class MYPROJECT_API AC_BaseCustomisedAI : public AC_BaseAI
{
	GENERATED_BODY()

public:

	AC_BaseCustomisedAI();

	UFUNCTION(BlueprintCallable)
	AActor* SpawnWeapon(TSubclassOf<AActor> WeaponClass, TSubclassOf<AActor> SickleClass);

	UFUNCTION(BlueprintCallable)
	AActor* SpawnTwoHandedWeapon(TSubclassOf<AActor> WeaponClass, TSubclassOf<AActor> SwordClass);

	UFUNCTION(BlueprintCallable)
	AActor* SpawnBackpack(TSubclassOf<AC_SkeletalMeshActor> BackpackClass);

	virtual void BeginPlay() override;

	AActor* Weapon;

	virtual void ResetMaterials() override;

	AActor* BackpackPTR;

protected:
	virtual void ChangeAIColour();

	UPROPERTY(EditAnywhere, Category = "Materials")
	FSkinColourMaterial SkinColourMaterial;

	UPROPERTY(EditAnywhere, Category = "Materials")
	FClothingColourMaterial ClothingColourMaterial;

	UPROPERTY(EditAnywhere, Category = "Melee")
	FMelee Melee;

	// The materials assigned to the mesh after customisation
	TArray<UMaterialInterface*> CustomisedMaterials;

	UFUNCTION(BlueprintCallable)
	void GetDefaultWeaponMaterials();

	UFUNCTION(BlueprintCallable)
	void GetDefaultBackpackMaterials();

	virtual void BecomeFrozen() override;

	virtual void BecomeUnFrozen() override;

private:

	UPROPERTY(EditAnywhere, Category = "Melee")
	FBackpack Backpack;

	void WeaponBecomeFrozen();

	void WeaponBecomeUnFrozen();

	TArray<UMaterialInterface*> DefaultWeaponMaterials;

	void BackpackBecomeFrozen();

	void BackpackBecomeUnFrozen();

	TArray<UMaterialInterface*> DefaultBackpackMaterials;
};
