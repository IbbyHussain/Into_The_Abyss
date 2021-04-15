// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h" 
#include "C_PlayerCharacter.generated.h"

// Used to update the text on player HUD that tracks the number of souls
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateNumberOfSouls, int, Number);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanTrade, int, num);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisableCurrentCombatState);

// Used to change collision on AI agents
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnteredMagicState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnteredRangedState);

// Game settings


class USpringArmComponent;
class UCameraComponent;
class UTimelineComponent;
class AC_ExitArea;
class UBoxComponent;
class UCurveFloat;
class AC_MudWall;
class AC_BaseAI;
class AC_IceSpike;
class AC_Crossbow;

// Melee Combat Struct
USTRUCT(BlueprintType)
struct FSS
{
	GENERATED_BODY()

	class AC_BaseSkeletalMeleeWeapon* Sword;
	//class AC_BaseMeleeWeapon* Sword;
	class AC_BaseShield* Shield;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	TSubclassOf<AC_BaseSkeletalMeleeWeapon> SwordClass;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	TSubclassOf<AC_BaseShield> ShieldClass;

	FName SwordSocket;
	FName ShieldSocket;
	FName SwordHiltSocket;
	FName SwordTipSocket;
	FName KickSocket;
	FName ShieldBashSocket;

	bool bContinueCombo;

	bool bIsAttacking;

	// used for a do once to make sure if the line trace hits does not hit again.
	//bool b1;

	int ComboCounter;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	UAnimMontage* DefaultAttack1;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	UAnimMontage* DefaultAttack2;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	UAnimMontage* DefaultAttack3;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	UAnimMontage* BlockingMontage;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	UAnimMontage* ShieldBashMontage;

	UPROPERTY(EditAnywhere, Category = "Sword and Shield")
	UAnimMontage* ThrustMontage;

	FTimerHandle ResetDamageHandle;

	TArray<AC_BaseAI*> AIArray;
	AC_BaseAI* AI;

	// Block Camera Shake
	UPROPERTY(EditDefaultsOnly, Category = "Sword and Shield")
	TSubclassOf<UCameraShake> BlockCameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sword and Shield")
	bool bIsBlocking;

	UPROPERTY(EditDefaultsOnly, Category = "Sword and Shield")
	USoundBase* ShieldHitSound;

	bool bCanBlock;

	// Checks if block button is pressed;
	bool bPressed1;

	// Used to stop spamming melee abilities
	bool bCanAttack;

	FTimerHandle ThrustHandle;

	bool bCanShieldBash;

	FTimerHandle ShieldBashHandle;

	// Default Constructor
	FSS()
	{
		SwordSocket = ("SwordSocket");

		ShieldSocket = ("ShieldSocket");

		SwordHiltSocket = ("Katana Hilt Socket");

		SwordTipSocket = ("Katana Tip Socket");

		KickSocket = ("KickSocket");

		ShieldBashSocket = ("ShieldBashSocket");

		bContinueCombo = false;

		bIsAttacking = false;

		//b1 = true;

		ComboCounter = 0;

		bCanBlock = true;

		bCanAttack = true;

		bCanShieldBash = true;
	}
};

USTRUCT(BlueprintType)
struct FCrossbow
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Crossbow")
	TSubclassOf<AC_Crossbow> CrossbowClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	AC_Crossbow* CrossbowObject;

	UPROPERTY(EditDefaultsOnly, Category = "Crossbow")
	USoundBase* FireSound;

	// Default socket
	FName CrossbowSocket;

	// socket used when aiming
	FName CrossbowAimingSocket;

	FName CrossbowCrouchedAimingSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Crossbow")
	UAnimationAsset* CrossbowReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Crossbow")
	UAnimationAsset* CrossbowReloadOpenMontage;

	bool bChooseOpen;

	FTimerHandle CanFireCrossbowandle;

	//Bolt switching

	int32 DummyBoltIndex;

	int32 CrossbowBoltIndex;

	// TSubclass as Bolts have a BP class, the current bolt equipped
	TSubclassOf<class AC_Crossbowbolt> CurrentBolt;

	TSubclassOf<class AC_DummyBolt> CurrentDummyBolt;

	// Zoom in

	// The curve used to smoothly interplate the player's FOV
	UPROPERTY(EditDefaultsOnly, Category = "Crossbow | Zoom In")
	UCurveFloat* FZoomInCurve;

	// Zoom in Timeline component
	UTimelineComponent* ZoomInTimelineComp;

	// The delegate called while the timeline plays (update)
	FOnTimelineFloat ZoomInInterpFunction{};

	// Default Constructor
	FCrossbow()
	{
		CrossbowSocket = ("CrossbowSocket");

		CrossbowAimingSocket = ("AimingSocket");

		CrossbowCrouchedAimingSocket = ("AimingCrouchSocket");

		bChooseOpen = true;
	}
};

UENUM()
enum class ECombatState : uint8
{
	UNARMED,
	MELEE,
	RANGED,
	MAGIC
};

UENUM()
enum class EAbilityType : uint8
{
	NONE,
	ABILITY1,
	ABILITY2,
	ABILITY3,
	ABILITY4
};

UENUM()
enum class EMovementState : uint8
{
	STANDING,
	CROUCHING,
	SLIDING,
	SWIMMING,
	DASHING,
	PUSHING,
	NONE
};

UCLASS()
class MYPROJECT_API AC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AC_PlayerCharacter();

	// Delegate used to update the number of souls
	UPROPERTY(BlueprintAssignable, Category = "aaa")
	FUpdateNumberOfSouls UpdatenumberOfSouls;

	UPROPERTY(BlueprintAssignable, Category = "aaa")
	FCanTrade CanTrade;

	// Delegate to disable the button for the current combat state
	UPROPERTY(BlueprintAssignable, Category = "aaa")
	FDisableCurrentCombatState DisableCurrentCombatState;

	UPROPERTY(BlueprintAssignable, Category = "aaa")
	FEnteredMagicState EnteredMagicState;

	UPROPERTY(BlueprintAssignable, Category = "aaa")
	FEnteredRangedState EnteredRangedState;


	void BroadcastCanTrade();

	bool bIsTrading;

	FHitResult HitResult;

	bool bHits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword and Shield")
	FSS SS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crossbow")
	FCrossbow Crossbow;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	EMovementState MovementState;

	bool bCanWalk;

	bool bLockCamera;

	UFUNCTION(BlueprintCallable)
	void DisablePlayerInput();

	UFUNCTION(BlueprintCallable)
	void EnablePlayerInput();

	//Combat State
	UPROPERTY( BlueprintReadWrite, Category = "Movement")
	ECombatState CombatState;

	void UpdateCombatState();

	//Camera 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	//Player Stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float Magic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	float Breath;

	int NumberOfSouls;

	//Box Component for the Player's head
	UPROPERTY(EditAnywhere, Category = "Camera")
	UBoxComponent* HeadCollisionComponent;

	//Player Movement
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bSprintKeyDown;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool CrouchKeydown;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsSliding;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bCanDash;

	// Crouching
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bCanCrouch;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bCanSlide;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsSlideUnlocked;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool IsDashUnlocked;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsCrouchUnlocked;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bCanUseWeaponWheel;

	//E Key Interactions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	bool bCanExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	bool bEKeyPressed;

	bool bCanOpenChest;

	bool bCanPullLever;

	bool bCanRotatePuzzle;

	bool bCanInteractWithAI;

	bool bOpenOnce;

	// Player Movement functions
	UFUNCTION(BlueprintCallable)
	void StopSwimming();

	UFUNCTION(BlueprintCallable)
	void ResolveMovement();

	UFUNCTION(BlueprintCallable)
	void UpdateMovement();

	//Damage Health
	void DamageOverTime();

	void StopDamageOverTime();

	//Water Volume 
	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	bool bInWaterVolume;

	UFUNCTION(BlueprintCallable)
	void WaterVolumeCheck();

	//Swap Time
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Swap Time Mechanic")
	class ATimeMechanicManagerClass* SwapTimeManager;

	void Pitch(float val);

	void Yaw(float val);

	bool bIsPushing;

	UPROPERTY(EditDefaultsOnly, Category = "Swap Time Mechanic")
	bool IsSprinting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Swap Time Mechanic")
	class AC_MoveableObjectManager* MoveableObjectManager;

	//Combat

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool bDisableWeaponWheel;

	bool bShowWeaponWheel;

	void ShowWeaponWheel();

	int32 CrossBowBolts;

	//AI Health Bar Detection

	
	UPrimitiveComponent* HitComp();

	AC_BaseAI* UpdateAI();

	AC_BaseAI* BaseAI;

	TArray<AC_BaseAI*> BaseAIArray;

	//Magic

	// The amount of damage ability 1 deals
	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability1DamageAmount;

	// Time betweeen each damage tick
	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability1RateOfDamage;

	// The amount of magicka this ability costs per DrainTime
	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability1DrainAmount;

	// Time between each Magicka drain tick
	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability1DrainTime;

	// The amount of Damage Ability2 Deals
	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability2Damage;

	// The time between each damage tick. 
	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability2RateOfDamage;

	//Used in ABP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ABP")
	bool bIsUsingAbility3;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall")
	float height;

	bool bStop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	class UParticleSystem* WallExplosion;

	class AC_RightHandMagic* RightHandMagic;
	class ALeftHandMagic* LeftHandMagic;

	// Used in abp for anim notify
	UFUNCTION(BlueprintCallable)
	void SpawnIceSpikes(TSubclassOf<AC_IceSpike> IceSpikeClass,FVector Location);

	UFUNCTION(BlueprintCallable)
	void Spawn3();

	UFUNCTION(BlueprintCallable)
	void FireIceSpikes();

	//Used in abp for anim notfiy
	UFUNCTION(BlueprintCallable)
	void ShowDefaultEffect();

	//Melee

	// Used in abp for anim notify
	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	//Used in abp for anim notify
	UFUNCTION(BlueprintCallable)
	void ContinueCombo();

	void MeleeAttackDamage(USkeletalMeshComponent* SKMesh, float Damage, bool bApplyDamageOverTime);

	FVector GetSwordHiltSocket();

	FVector GetSwordTipSocket();

	void ResetAttackVar();

	void Rag(USkeletalMeshComponent* SKMesh);

	// Crossbow

	void BasicSpawnCrossbow();

	//Used in ABP 
	UFUNCTION(BlueprintCallable)
	void ResetCrossbowCooldown();

	// BoltSwitching

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	void SwitchBolts(int Index);

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	int EvaluateNextBolt();

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	int EvaluatePreviousBolt(int LastIndex);

	// Dummy Bolt switching

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	void SwitchDummyBolts(int Index);

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	int EvaluateNextDummyBolt();

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	int EvaluatePreviousDummyBolt(int LastIndex);

	// Bolt Icon Switching

	int BoltIconIndex;

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	void SwitchBoltIcon(int Index);

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	int EvaluateNextBoltIcon();

	// Used in player BP
	UFUNCTION(BlueprintCallable)
	int EvaluatePreviousBoltIcon(int LastIndex);

	void CreateCrossbowBoltTracker();

	void DestroyCrossbowBoltTracker();

	// Used in flare bolt pickup
	void SpawnCircleIndicator(FVector Location);

	// Flare Bolt Indicator
	void ShouldSpawnFlareBoltIndicator();

	// Saving Data

	UFUNCTION(BlueprintCallable)
	void SavePlayerLocation();

	UFUNCTION(BlueprintCallable)
	void LoadPlayerLocation();

	UFUNCTION(BlueprintCallable)
	void ResetBolts();

	// Used for bolt pickup
	void UpdateNumberOfBolts(int32& Bolt);

	// Used in ABP to switch aim offsets
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ABP")
	bool bAim;

	UFUNCTION(BlueprintCallable)
	void BlockImpact();

	UFUNCTION(BlueprintCallable)
	void ABPStartBlocking();

	void StaggerAI(USkeletalMeshComponent* SKMesh);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ABP")
	bool bCanUseAbility3;

	// used in flare bolt 
	class AC_SkeletalMeshActor* FlareBoltIndicator;

	// Used in bolt pickups 
	void SpawnDummyBolt();

	UFUNCTION(BlueprintCallable)
	void SaveNumberOfSouls();

	UFUNCTION(BlueprintCallable)
	void LoadNumberOfSouls();

	// used in AI trader
	UFUNCTION()
	void StopSprint();

	// Damage

	// Used in AI classes
	UFUNCTION(BlueprintCallable)
	void ApplyDamageToPlayer(float DamageAmount);

	void TakeDamage();

	void CheckForPlayerDeath();

	void PlayerDeath();

	void Respawn();

	// Var used to control if player can exeute any key input
	bool bHasDied;

	FTimerHandle RestartLevelHandle;

	void EnableRespawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	UAnimMontage* PlayerDeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	USoundBase* PlayerHitSound;
	

	// Used to apply stealth Multiplier when in crossbow state
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Crossbow")
	bool bIsHidden;

	// Used in exit area class, to fix player movement after exiting swimming area
	void ExitAreaFixMovement();

	AActor* InteractHitActor;

	// used to disable interactions when in cutscenes
	bool bCanInteract;

	UFUNCTION(BlueprintCallable)
	void LockedAbilities(bool bIsDashLocked, bool bIsCrouchLocked, bool bIsSlideLocked, bool bIsWeaponWheelLocked);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	bool bOpenSettings;


	// Settings

	// Will set the sound to the saved volume
	void SetSoundVolume();

	void DestroyTempSoundWidget();

	bool bDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magic")
	AC_MudWall* MudWallActor;

private:

	//Idle
	bool bIsIdle;

	void CheckIdle();

	// Basic Player Movement
	void MoveForward(float Axis);

	void MoveRight(float Axis);

	// Jumping
	bool bIsJumping;

	bool bCanJump;

	int DoubleJumpCounter;

	FVector JumpHeight;

	FTimerHandle JumpDelayHandle;

	void PlayerJump();

	void CanJump();

	bool bCanSprint;

	float SprintDrain;

	FTimerHandle StaminaDecreaseHandle;

	void CheckSprint();

	void DecreaseStamina();

	// Sprint Camera Shake
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	TSubclassOf<UCameraShake> SprintCameraShake;

	void PlaySprintCameraShake();

	UFUNCTION()
	void Sprint();

	// Dashing
	float DashDistance;

	float DashCoolDown;

	float DashStop;

	FTimerHandle DashHandle;

	FTimerHandle DashStopHandle;

	UFUNCTION()
	void Dash();

	UFUNCTION()
	void StopDashing();

	UFUNCTION()
	void ResetDash();

	//Sliding

	float SlideACOs1;

	FVector SlideDirection;

	FTimerHandle SlideDelayTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FSlideCurve;

	UTimelineComponent* SlideTimeline;

	FOnTimelineFloat SlideInterpFunction{};

	FOnTimelineEvent SlideTimelineFinished{};

	UFUNCTION()
	void SlideTimelineFloatReturn(float Value);

	UFUNCTION()
	void OnSlideTimelineFinished();

	UFUNCTION()
	void Slide();

	void ResetSlide();

	// Swimming
	float SwimmingCapsuleHeight;

	float SwimmingCapsuleRadius;

	float DefaultMeshHeight;

	float CrouchedMeshHeight;

	float MeshX;

	float MeshY;

	float SwimMeshHeight;

	float SwimMovingMeshHeight;

	FTimerHandle DamageOverTimeHandle;

	UTimelineComponent* SwimTimeLine;

	UPROPERTY(EditAnywhere, Category = "Timeine")
	UCurveFloat* FSwimCurve;

	UFUNCTION()
	void SwimTimelineFloatReturn(float Value);

	FOnTimelineFloat SwimInterpFunction{};

	void CheckSwimmingMeshHeight();

	float DefaultCameraHeight;

	float CrouchedCameraHeight;

	float DefaultCapsuleHeight;

	float CrouchedCapsuleHeight;

	FTimerHandle CrouchDelayTimerHandle;

	UTimelineComponent* CrouchTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FCrouchCurve;

	void CustomCrouch();

	void ResetCrouch();

	void StopCustomCrouch();

	UFUNCTION()
	void CrouchTimelineFloatReturn(float Value);

	FOnTimelineFloat CrouchInterpFunction{};

	FOnTimelineEvent CrouchTimelineFinished{};

	//Player's Velocity
	FVector PlayersVelocity;

	float PlayersVelocityMagnitude;

	// E KEY Interactions
	FTimerHandle ExitAreaHandle;


	void ExitAreaReleased();

	void SetCanExit();

	UFUNCTION()
	void ExitArea();

	// Swap Time Mechanic 

	void SwapTime();

	bool ChooseA;

	// Misc
	FTimerHandle testHandle;

	//References
	class AC_PlayerHUD2* HUD;

	//Magic

	EAbilityType AbilityType;

	void UpdateAbility();

	void AddMagicEffects();

	void RemoveMagicEffects();

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	TSubclassOf<class AC_RightHandMagic> RightHandMagicClass;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	TSubclassOf<class ALeftHandMagic> LeftHandMagicClass;

	FName RightHandSocket;

	FName LeftHandSocket;

	// If sprinting will release current ability
	void ReleaseAbilities();

	// Ability 1

	// Animation Montage used for Ability1 
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAnimMontage* Ability1Animation;

	void Ability1();

	void Ability1Released();

	bool bCanUseAbility1;

	bool bIsUsingAbility1;

	FTimerHandle FlameHandle;

	FTimerHandle FlameHandle2;

	TArray<FHitResult> Ability1Damage();

	UFUNCTION()
	void ApplyAbility1Damage();

	UFUNCTION()
	void MagickaDrain(float Amount, float Time);

	FTimerHandle MagickaDrainHandle;

	void Ability1Check();

	void ShowAbility1Effect();

	void SpawnFlameParticles();

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UParticleSystem* FlamesParticle;

	UPROPERTY()
	UParticleSystemComponent* LeftHandFlamesParticle;
	UPROPERTY()
	UParticleSystemComponent* RightHandFlamesParticle;

	void DespawnFlamesParticles();

	void RotateIdleMagic();

	void ResetIdleMagicRotation();

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Abilities")
	USoundBase* FlamesStartSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Abilities")
	USoundBase* FlamesLoopSound;

	UPROPERTY()
	UAudioComponent* FlamesStartSoundComp;

	UPROPERTY()
	UAudioComponent* FlamesLoopSoundComp;

	UPROPERTY()
	FTimerHandle StartFlamesLoopSoundHandle;

	UFUNCTION()
	void StartFlameLoopSound();

	UFUNCTION()
	void StopFlamesSounds();

	// Particle Fade out

	UFUNCTION()
	void PlayFlamesMaterialFadeOut();

	FTimerHandle FlamesFadeOutHandle;

	// The curve that controlls how the material will fade out
	UPROPERTY(EditDefaultsOnly, Category = "Abilities | Ability1")
	UCurveFloat* FMaterialFadeCurve;

	// The material of the particle
	UPROPERTY(EditDefaultsOnly, Category = "Abilities | Ability1")
	UMaterialInterface* FlamesMaterial;

	UFUNCTION()
	void MaterialFadeTimelineFloatReturn(float Alpha);

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicFlamesMaterial;

	UTimelineComponent* MaterialFadeTimeline;

	FOnTimelineFloat MaterialFadeInterpFunction{};

	// Ability 2

	UPROPERTY(EditDefaultsOnly, Category = "Sounds | Abilities")
	USoundBase* Ability2Sound;

	UAudioComponent* Ability2SoundComp;

	FTimerHandle Ability2SoundHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAnimMontage* Ability2Animation;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAnimMontage* Ability2EndAnimation;

	void Ability2();

	void Ability2Check();

	bool bDo;

	bool bTest;

	FTimerHandle Ability2Handle;

	FTimerHandle DestroyAbility2Handle;

	void Ability2Released();

	void SpawnSwords();

	void DespawnSwords();

	bool bCanUseAbility2;

	bool bIsUsingAbility2;

	class AC_Ability2* Ability2Actor;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	TSubclassOf<class AC_Ability2> Ability2Class;

	FName BackSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability2DrainAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability2DrainTime;

	void ShowAbility2Effect();

	void StartAbility2Sound();

	// Ability 3

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAnimMontage* Ability3Animation;

	void Ability3();

	void PlayAbility3Animation();

	FTimerHandle Ability3AnimationHandle;

	void SpawnWall();

	FName HipsSocket;

	UPROPERTY()
	TArray<AC_MudWall*> WallArray;

	TArray<int32> nums;

	FName RootSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Magic")
	TSubclassOf<class AC_MudWall> MudWallClass;

	AC_MudWall* SpawnWallActor();

	FVector WallEndLocation;

	bool b1 = true;
	bool b2;
	bool b3;

	void Ability3Released();

	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability3DrainAmount;

	void ShowAbility3Effect();

	// Ability 4

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	UAnimMontage* Ability4Animation;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities Stats")
	float Ability4DrainAmount;

	void Ability4();

	void Ability4Released();

	bool bCanUseAbility4;

	bool bIsUsingAbility4;

	void ShowAbility4Effect();

	UPROPERTY(EditDefaultsOnly, Category = "Ability4")
	TSubclassOf<AC_IceSpike> MiddleIceSpikeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability4")
	TSubclassOf<AC_IceSpike> LeftIceSpikeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability4")
	TSubclassOf<AC_IceSpike> RightIceSpikeClass;

	AC_IceSpike* IceSpike;

	FName ProjectileSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Ability4")
	FVector MuzzleOffset;

	TArray<AC_IceSpike*> IceSpikeArray;

	// Sword and Shield

	void AddSS();

	void RemoveSS();

	void SelectAttackAnimation();

	void DefaultAttack();

	void SetMeleeCamera();

	void ResetMeleeCamera();

	// Blocking
	
	void StartBlocking();

	void StopBlocking();

	void CheckBlock();

	// Shield Bash
	void ShieldBash();

	void EnableShieldBash();

	// Thrust

	void Thrust();

	void EnableThrust();

	// Crossbow

	void MakeCrossbowVisible();

	void MakeCrossbowInVisible();

	void SpawnCrossbow();

	void DespawnCrossbow();

	void FireCrossbow();

	bool bCanFireCrossbow;

	void DespawnDummyBolt();

	void ReloadCrossbow();

	void AddCircleBoltIndicator();

	int32 counter;

	UPROPERTY(EditDefaultsOnly, Category = "Crossbow")
	TSubclassOf<class AC_SkeletalMeshActor> FlareBoltIndicatorClass;

	void AimCrossbow();

	void StopAimCrossbow();

	UFUNCTION(BlueprintCallable)
	void ChangeCrossbowTransform(FName Socket);

	UFUNCTION(BlueprintCallable)
	void ResetCrossbowTransform(FName Socket);

	// The function that plays while the timeline updates
	UFUNCTION()
	void ZoomInTimelineFloatReturn(float Delta);

	void CrouchCrossbowTransform();

	void FlareBoltIndicatorCheck();

	// When the crossbow moves from aiming to idle clips with hand
	void MakeHandInvisible();

	void MakeHandvisible();

	FTimerHandle InvisibleHandHandle;

	// Used when aiming will set the dummy bolt to the aiming transform via spawning a new dummy bolt
	void SpawnDummyBoltForAiming();

	FTimerHandle SpawnHandle;

	//Damage

	FTimerHandle BurnHandle;

	FVector SpawnLocation2;

	// Interact System

	// Used to detect if overlapping with interactable object
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Interact();

	// General

	// Changes the players materials to opacity of 0
	UFUNCTION(BlueprintCallable)
	void MakePlayerInvisible();

	// Resets the player materials to defaults
	UFUNCTION(BlueprintCallable)
	void MakePlayerVisible();

	UPROPERTY(EditDefaultsOnly, Category = "General")
	UMaterial* InvisibleMaterial;

	TArray<UMaterialInterface*> GetDefaultMaterials();

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TArray<UMaterialInterface*> PlayerMaterials;

	// settings

	void OpenSettingsMenu();

};