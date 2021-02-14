// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_BaseAI.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FMeleeState
{
	GENERATED_BODY()

	FMeleeState()
	{

	}
};

// Enum class that holds all the different types of AI, for ABP
UENUM()
enum class ETypeOfAI : uint8
{
	PEASANT,
	SAVAGE,
	ARCHER,
	MAGE,
	TRADER
};

// Enum class that holds all the different types of death for AI
UENUM()
enum class ETypeOfDeath : uint8
{
	DEFAULTDEATH,
	ABILITY1DEATH,
	ABILITY2DEATH
};


UCLASS()
class MYPROJECT_API AC_BaseAI : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Melee State")
	FMeleeState MeleeState;

	//Used in ABP to determine which Death anim to play
	UPROPERTY(BlueprintReadOnly, Category = "Base AI Variables")
	ETypeOfDeath TypeOfDeath;

	UPROPERTY(BlueprintReadWrite, Category = "Base AI Variables")
	ETypeOfAI TypeOfAI;

	// Sets default values for this character's properties
	AC_BaseAI();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Base AI Variables")
	FString AIName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base AI Variables")
	class UC_HealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category = "Base AI Variables")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	TSubclassOf<AActor> PickupClass;

	class AC_SoulsPickup* SoulsPickup;

	bool bIsBurning;

	void StartDamage();

	void StopDamage();

	//FTimerHandle Handle;

	//BURN Damage Amount
	UPROPERTY(EditAnywhere)
	float Amount;

	//Used to dictate when to apply burning damage to this AI (Used by ability 1)
	bool bHasBeenHit;

	void Death();

	FTimerHandle DespawnHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* DeathAnimation;

	// Used in abp
	UPROPERTY(BlueprintReadOnly, Category = "Base AI Variables")
	bool bHasDied;

	FTimerHandle DeathHandle;

	// ALLOWS IT TO BIND ITSELF
	UFUNCTION()
	void UpdateHealth(UC_HealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);

	class AC_Ability2* Ability2;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Rag doll

	FTimerHandle RagdollHandle;

	FTimerHandle RagdollResetHandle;

	void ApplyRagdoll();

	//void RemoveRagdoll();

	bool bStopRagdoll;

	bool bInRagdoll;

	// Hips bone name
	FName HipsBone;

	// Hips socket name
	FName HipsSocket;

	FName NeckSocket;

	// Moves the AI's capsule with the mesh
	//void UpdateCapsuleLocation();


	void RagdollCooldown();

	FTimerHandle RagdollCooldownHandle;

	bool bIsRagdollTimerActive;

	//Checks if currently overlapping with AI's box comp
	bool bOverlapping;

	void StartRagdollTimer();

	void CheckForAIDeath();


	//Ragdoll Physics

	// Used in ABP
	UPROPERTY(BlueprintReadOnly, Category = "Base AI Variables")
	bool bIsSimulatingPhysics;

	// Used in ABP
	UPROPERTY(BlueprintReadOnly, Category = "Base AI Variables")
	bool bHasStopped;

	UFUNCTION(BlueprintCallable)
	void EnableRagdoll();

	UFUNCTION(BlueprintCallable)
	void StartDisableRagdoll();

	// Used in ABP for anim notify
	UFUNCTION(BlueprintCallable)
	void EnableMovement();

	// Virtual frozne functions so that if a Base_Customised AI becomes frozen their accessories can also become frozen

	virtual void BecomeFrozen();

	virtual void BecomeUnFrozen();

	// Used in abp
	UPROPERTY(BlueprintReadOnly, Category = "Base AI Variables")
	bool bIsFrozen;

	void Shatter();

	// used for a do once to make sure if the line trace hits does not hit again.
	bool bCanBeAttacked;

	// Used for immunity to shield bash 
	bool bCanBeShieldBashed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Crystal cCrossbow Bolt

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* BlindAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* StaggeredAnimation;

	FTimerHandle BlindnessHandle;

	UFUNCTION()
	void BecomeBlind(UAnimMontage* MontageToPlay, float TimeUntilRecover);

	UFUNCTION()
	void RemoveBlindness(UAnimMontage* MontageToStop);

	FTimerDelegate TimerDel;

	// Apply damage to AI
	void StartDamageOverTime(float DamageAmount, float DamageTick, float Time);

	FTimerHandle DamageOverTimeHandle;

	FTimerDelegate DamageOverTimeDelegate;

	UFUNCTION()
	void ApplyDamageToAI(float DamageAmount);

	void EndDamageOverTime();

	// Will destroy the spawned items when the AI is shattered
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ZZZ")
	void DestroyAIItems();

	// When the AI takes damage from a fire source 
	void SpawnBurningEffects();

	void DespawnBurningEffects();

	UFUNCTION()
	void MagicStateCollision();

	UFUNCTION()
	void RangedStateCollision();

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* BoltHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* HitGrunt;

	void PlayBoltHitMontage();

	bool bCanRagdoll;

	void Staggered();

	FTimerHandle StaggeredHandle;

	void RecoverFromStagger();

	// Used in Notfiy state
	UFUNCTION(BlueprintCallable)
	void UpdateCapsuleForAnimations();

	void PlayHitGrunt();

	// Used when the player hits the AI, and the AI is not currently focused on player
	void ShouldFocusOnPlayer();

protected:
	// Used in the blueprint of this class
	UFUNCTION(BlueprintCallable)
	AActor* SpawnItem(FName SocketName, AActor* Item, bool bShouldBeAttached, TSubclassOf<AActor> ItemClass);

	void ChangeColours(bool bRandomColours, TArray<UMaterialInstanceDynamic*> MaterialArray, int MaxArrayAmount,
		int MaterialIndex);

	FString DisplayText(FString AIText);

	// Interact

	class AC_PlayerCharacter* PlayerCharacter;

	bool bShowEKeyHint;

	class AC_PlayerHUD2* HUD;

	bool OverlappingLeverBoxCollision();

	bool bOverlappingPlayer;

	bool bCanTalkAI;

	// Used for ai that need to do something unique on death
	virtual void OnDeath();

	// Materials, use for customised AI 

	virtual void ResetMaterials();

	//Material used when frozen
	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInterface* FrozenMaterial;

private:

	TArray<UMaterialInterface*> DefaultMaterials;

	//The destructible mesh that will be used when the character becomes frozen.
	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4")
	class UDestructibleComponent* DestructibleMeshComp;

	// Ability2 Damage

	UFUNCTION()
	void ApplyDamage2();

	// The time between each damage tick
	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 2")
	float Ability2Rate;

	// The amount of damage the ability will deal
	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 2")
	float Ability2DamageAmount;

	FTimerHandle Ability2DamageHandle;

	//Ragdoll Physics

	FVector MeshLocation;

	FVector CapsuleLocation;

	bool bIsFacingUpwards;

	// The montage to use when standing up(will either be standupfromback or standupfromstomach)
	UAnimMontage* StandUpMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Ragdoll")
	UAnimMontage* StandUpFromBackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Ragdoll")
	UAnimMontage* StandUpFromStomachMontage;

	void DisableRagdoll();

	void UpdateCapsule();

	void CachePose();

	void CalculateMeshLocation();

	FTimerHandle DisableRagdollHandle;

	FTimerHandle EnableMovementHandle;

	bool CalculateFacingDirectionC();

	void UpdateStandingOrientation();

	void UpdateStandingMontage();

	FTimerHandle FrameSkipHandle;

	void bfunction();

	// Name of the snap shot pose
	FName SnapShotName;

	//Materials 

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material0;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material1;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material2;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material3;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material4;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material5;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Materials")
	UMaterialInstance* Material6;

	FTimerHandle BecomeUnFrozenHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Frozen poses")
	UAnimMontage* FrozenPose1;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Frozen poses")
	UAnimMontage* FrozenPose2;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4|Frozen poses")
	UAnimMontage* FrozenPose3;

	TArray<UAnimMontage*> FrozenMontageArray;

	bool bPlayFrozenPose;

	bool bDoOnce;

	// The sound played when the AI becomes becomes destructible
	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability 4")
	USoundBase* ShatteredSound;

	//Destroy this object
	void DestroyThis();

	FTimerHandle DestroyHandle;

	// Melee damage

	void MeleeAttackDamage(USkeletalMeshComponent* SKMesh);

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Player Abilities|Ability1")
	UParticleSystem* FireParticleEffect;

	// Reference to all particle systems that need to be spawned
	UParticleSystemComponent* FireParticleSystemComponentShoulder;
	UParticleSystemComponent* FireParticleSystemComponentChest;
	UParticleSystemComponent* FireParticleSystemComponentLeg;

	TArray<UParticleSystemComponent*> FireParticleSystemComponentArray;

	bool bHasSpawnedFireEffects;
};
