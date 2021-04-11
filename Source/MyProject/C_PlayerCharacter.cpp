#include "C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/C_PlayerHUD2.h"
#include "GameObjects/Volumes/C_ExitArea.h"
#include "EngineUtils.h"
#include "Math/Vector.h"
#include "Components/BoxComponent.h"
#include "TimeMechanicManagerClass.h"
#include "Kismet/KismetSystemLibrary.h" // for the debug line and other trace types
#include "MyProject/ManagerClasses/C_MoveableObjectManager.h"
#include "MyProject/Components/C_HealthComponent.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject\MyProject.h"
#include "MyProject/Misc/LeftHandMagic.h"
#include "MyProject/Misc/C_RightHandMagic.h"
#include "Math/Quat.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimMontage.h"
#include "MyProject/Misc/C_Ability2.h"
#include "MyProject/Misc/C_MudWall.h"
#include "Particles/ParticleSystem.h"
#include "MyProject/Misc/C_IceSpike.h"

#include "Engine/CollisionProfile.h"

#include "MyProject/UI/Settings/C_SettingsSoundWidget.h"
#include "MyProject/UI/Settings/C_SettingsVideoWidget.h"

// Sword and Shield includes
#include "MyProject/Weapons/MeleeWeapons/C_BaseSkeletalMeleeWeapon.h"
//#include "MyProject/Weapons/MeleeWeapons/C_BaseMeleeWeapon.h"
#include "MyProject/Weapons/Shields/C_BaseShield.h"

// Interact includes (Interactable objects)
#include "MyProject/GameObjects/SkeletalMeshs/Chests/C_ChestActorBase.h"
#include "MyProject/GameObjects/SkeletalMeshs/Levers/C_BaseAnimLever.h"
#include "MyProject/GameObjects/StaticMeshs/Interactables/Puzzles/C_RotatingPuzzleActor.h"

// Pickup Includes
#include "MyProject/GameObjects/Staticmeshs/Interactables/Pickups/C_Pickup.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_HealthPickup.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_StaminaPickup.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_ManaPickup.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SoulsPickup.h"
#include  "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/Bolt Pickups/C_SteelBoltPickup.h"

#include "PhysicalMaterials/PhysicalMaterial.h"

#include "MyProject/Weapons/Crossbow/C_DummyBolt.h"
#include "MyProject/UI/C_CrossBowBoltTracker.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "MyProject/Weapons/Crossbow/C_SteelBolt.h"
#include "MyProject/Weapons/Crossbow/Bolts/C_FlareBolt.h"

#include "MyProject/Misc/C_BaseSaveGame.h"

#include "MyProject/GameObjects/C_StaticMeshActor.h"

#include "MyProject/Components/C_CameraComponent.h"

#include "Components/AudioComponent.h"

#include "AI/EnglishEnemies/C_PeasantAI.h"
#include "MyProject/AI/Creatures/C_LostAdventurer.h"
#include "MyProject/AI/Creatures/C_RollerAI.h"
//#include "MyProject/Misc/C_Checkpoint.h"

//Constructor
AC_PlayerCharacter::AC_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Basic Movement
	bCanWalk = true;

	// Camera 
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(GetMesh(), "CameraLocation");
	CameraComp->bUsePawnControlRotation = true;

	// Head Collision 
	HeadCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	HeadCollisionComponent->SetupAttachment(GetMesh(), "CameraLocation");

	// Character Settings 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Player stats
	Health = 75.0f;
	Stamina = 50.0f;
	Magic = 25.0f;
	Breath = 100.0f;
	NumberOfSouls = 0;

	// Character Movement Settings
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.75f;

	// Jump
	DoubleJumpCounter = 0;
	bIsJumping = false;
	bCanJump = true;
	JumpHeight = FVector(0.0f, 0.0f, 600.0f);

	// Dash
	bCanDash = true;
	DashDistance = 6000.0f;
	DashCoolDown = 1.0f;
	DashStop = 0.1;

	// Sprinting
	//bIsSprinting = false;
	SprintDrain = 0.05;
	bCanSprint = true;

	// Crouching
	bCanCrouch = true;

	bIsCrouchUnlocked = true;

	IsDashUnlocked = true;

	bIsSlideUnlocked = true;

	//Crouch Timeline
	CrouchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeline"));
	CrouchInterpFunction.BindUFunction(this, FName("CrouchTimelineFloatReturn"));

	// Sliding
	bCanSlide = true;

	// Slide Timeline
	SlideTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SlideTimeline"));
	SlideInterpFunction.BindUFunction(this, FName("SlideTimelineFloatReturn"));
	SlideTimelineFinished.BindUFunction(this, FName("OnSlideTimelineFinished"));

	// Swim Timeline
	SwimTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("SwimTimeline"));
	SwimInterpFunction.BindUFunction(this, FName("SwimTimelineFloatReturn"));

	//Time Swap Mechanic
	ChooseA = true;

	//Show Weapon Wheel
	bShowWeaponWheel = true;

	bDisableWeaponWheel = false;

	//E Key Interactions
	bEKeyPressed = false;

	bOpenOnce = true;

	bCanRotatePuzzle = true;

	bCanInteract = true;

	//Water Volume
	bInWaterVolume = false;

	//Combat
	CrossBowBolts = 32;

	RightHandSocket = ("RightHandSocket");

	LeftHandSocket = ("LeftHandSocket");

	HipsSocket = ("HipsSocket");

	RootSocket = ("RootSocket");

	ProjectileSocket = ("ProjectileSocket");

	//Ability 1 

	Ability1DamageAmount = 0.001f;

	Ability1DrainAmount = 0.5f;

	Ability1DrainTime = 0.01f;

	Ability1RateOfDamage = 0.01f;

	//Ability 2

	Ability2RateOfDamage = 1.0f;

	Ability2Damage = 0.1f;

	Ability2DrainAmount = 1.0f;

	Ability2DrainTime = 0.01f;

	BackSocket = ("BackSocket");


	bCanUseAbility1 = true;

	bCanUseAbility2 = true;

	bCanUseAbility3 = true;

	bCanUseAbility4 = true;

	// Crossbow
	bCanFireCrossbow = true;

	// Create timeline component
	Crossbow.ZoomInTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("ZoomInTimeline"));

	// Bind the function to the delegate 
	Crossbow.ZoomInInterpFunction.BindUFunction(this, FName("ZoomInTimelineFloatReturn"));

	// Overlap Functions

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerCharacter::OnOverlapBegin);

	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AC_PlayerCharacter::OnOverlapEnd);

	// Dynamic material fade for ability 1
	MaterialFadeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Material Fade Timeline"));
	MaterialFadeInterpFunction.BindUFunction(this, FName("MaterialFadeTimelineFloatReturn"));

	bOpenSettings = true;
}

// Begin play
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Loads the currency of the player
	//LoadNumberOfSouls();

	//References
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	// Sets the default settings of the character 
	DefaultCameraHeight = CameraComp->GetRelativeLocation().Z;
	DefaultCapsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	DefaultMeshHeight = GetMesh()->GetRelativeLocation().Z;

	// Sets the crouched settings of the character 
	CrouchedCameraHeight = DefaultCameraHeight * 0.5;
	CrouchedCapsuleHeight = DefaultCapsuleHeight * 0.7;
	CrouchedMeshHeight = DefaultMeshHeight / 1.5f;

	// Sets the swimming settings of the character
	SwimmingCapsuleHeight = 30.0f;
	SwimmingCapsuleRadius = 30.0f;
	SwimMeshHeight = DefaultMeshHeight / 0.75f;
	
	//Sets the default speed of the player
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	SpawnCrossbow();

	LoadNumberOfSouls();

	LoadPlayerLocation();

	//Sets the values of the crouch timeline
	if (FCrouchCurve)
	{
		CrouchTimeline->AddInterpFloat(FCrouchCurve, CrouchInterpFunction, FName("Alpha"));
		CrouchTimeline->SetLooping(false);
		CrouchTimeline->SetIgnoreTimeDilation(true);
	}

	//Sets the values of the slide timeline
	if (FSlideCurve)
	{
		SlideTimeline->AddInterpFloat(FSlideCurve, SlideInterpFunction, FName("Bravo"));
		SlideTimeline->SetTimelineFinishedFunc(SlideTimelineFinished);
		SlideTimeline->SetLooping(false);
	}

	//Sets the values of the Swim timeline
	if(FSwimCurve)
	{
		SwimTimeLine->AddInterpFloat(FSwimCurve, SwimInterpFunction, FName("Charlie"));
		SwimTimeLine->SetLooping(false);
	}

	// Sets values of Zoom in timeline
	if(Crossbow.FZoomInCurve)
	{
		Crossbow.ZoomInTimelineComp->AddInterpFloat(Crossbow.FZoomInCurve, Crossbow.ZoomInInterpFunction, FName("Delta"));
		Crossbow.ZoomInTimelineComp->SetLooping(false);
	}

	//Creates dynamic material
	DynamicFlamesMaterial = UMaterialInstanceDynamic::Create(FlamesMaterial, this);

	//Fade Flamesparticle material Timeline setup
	if (FMaterialFadeCurve)
	{
		MaterialFadeTimeline->AddInterpFloat(FMaterialFadeCurve, MaterialFadeInterpFunction, FName("Euphemia"));
		MaterialFadeTimeline->SetLooping(false);
	}

	// draw debug cirlce around player
	//FTransform PlayerTransform = GetActorTransform();
	//DrawDebugCircle(GetWorld(), PlayerTransform.ToMatrixWithScale(), 300.0f, 25, FColor::Purple, false, 20.0f, 1, 2.0f, false);
	//DrawDebugCircle(GetWorld(), PlayerTransform, 300.0f, 25, FColor::Purple, true, 10.0f);

	SetSoundVolume();
}

// Tick
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sets the Players velocity and gets the magnitude.
	PlayersVelocity = AC_PlayerCharacter::GetVelocity();
	PlayersVelocityMagnitude = PlayersVelocity.Size();

	// Stop sprinting if we are falling or run out of stamina
	if (GetCharacterMovement()->IsFalling() == true || Stamina < SprintDrain)
	{
		StopSprint();
		bCanCrouch = false;
	}


	CheckSwimmingMeshHeight();

	CheckSprint();

	WaterVolumeCheck();

	UpdateAI();

	//Ability 1 Check
	Ability1Check();

	//Ability 2 Check
	Ability2Check();

	//AddCircleBoltIndicator();

	//CrouchCrossbowTransform();

	// Call whenever we receive stamina
	CheckBlock();

	//UE_LOG(LogTemp, Error, TEXT("Status: %s "), (bCanAttack ? TEXT("CAN ATTACK") : TEXT("CANT ATTACK")));

	if (bLockCamera)
	{
		GetMesh()->SetVisibility(false);
		GetMesh()->bCastDynamicShadow = false;
	}

	else
	{
		GetMesh()->SetVisibility(true);
		GetMesh()->bCastDynamicShadow = true;
	}
}

// PLAYER MOVEMENT

// Check Idle
void AC_PlayerCharacter::CheckIdle()
{
	if (PlayersVelocityMagnitude == 0.0f)
	{
		bIsIdle = true;
		bSprintKeyDown = false;
	}

	if (PlayersVelocityMagnitude != 0.0f)
	{
		bIsIdle = false;
	}
}

// Basic Movement (Forwards and Backwards)
void AC_PlayerCharacter::MoveForward(float Axis)
{
	//If we are not sliding we have access to the W,S keys
	if (MovementState != EMovementState::SLIDING && MovementState != EMovementState::SWIMMING && bCanWalk)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Gets the forward vector of the player and moves in the forwrads or backwards direction
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}

	// Swimming Movement
	if (MovementState == EMovementState::SWIMMING)
	{
		FRotator CameraRot = CameraComp->GetRelativeRotation();
		FVector ForwardCamera = CameraComp->GetForwardVector();
		AddMovementInput(ForwardCamera, Axis);
	}
}

// Basic Movement (Right and Left)
void AC_PlayerCharacter::MoveRight(float Axis)
{
	//If we are not sliding we have access to the A,D keys
	if (MovementState != EMovementState::SLIDING && bCanWalk)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Gets the left/right vector of the player and moves in the left or right direction
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

// Jump 
void AC_PlayerCharacter::PlayerJump()
{
	if (bCanJump && DoubleJumpCounter <= 1)
	{
		DoubleJumpCounter++;
		bCanJump = false;
		AC_PlayerCharacter::LaunchCharacter(JumpHeight, false, true);

		//Jump Timer so jump cannot be spammed.
		GetWorldTimerManager().SetTimer(JumpDelayHandle, this, &AC_PlayerCharacter::CanJump, 0.65f, false);
	}
}

// Can Jump
void AC_PlayerCharacter::CanJump()
{
	bCanJump = true;
}

// Jump Landed
void AC_PlayerCharacter::Landed(const FHitResult& Hit)
{
	DoubleJumpCounter = 0;
	if(CombatState == ECombatState::UNARMED || CombatState == ECombatState::RANGED)
	{
		bCanCrouch = true;
	}
}

// Sprint
void AC_PlayerCharacter::Sprint()
{
	IsSprinting = true;
	bSprintKeyDown = true;
	GetWorldTimerManager().SetTimer(StaminaDecreaseHandle, this, &AC_PlayerCharacter::DecreaseStamina, 0.01f, true);
}

// Stop Sprint
void AC_PlayerCharacter::StopSprint()
{
	IsSprinting = false;
	bSprintKeyDown = false;
	if (MovementState == EMovementState::STANDING)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		//bCanFireCrossbow = true;
	}

	GetWorldTimerManager().ClearTimer(StaminaDecreaseHandle);
}

//Check Sprint
void AC_PlayerCharacter::CheckSprint()
{
	// Calculates the direction the player is moving in using dot product.
	FVector LocalPlayerVelocity = GetVelocity();

	float SprintDirectionDotProduct = LocalPlayerVelocity.DotProduct(LocalPlayerVelocity, GetActorForwardVector());
	float SprintACOs = UKismetMathLibrary::DegAcos(SprintDirectionDotProduct);

	// If the player is sprinting moving in the forward direction
	if (IsSprinting && SprintACOs != 180.0f && PlayersVelocityMagnitude != 0.0f)
	{
		bSprintKeyDown = true;
		if (MovementState == EMovementState::STANDING)
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200.0f;

			//Stops Camera shake if the player is in magic state
			if (CombatState != ECombatState::MAGIC)
			{
				PlaySprintCameraShake();
			}

			if(SS.bIsBlocking)
			{
				StopBlocking();
			}

			ReleaseAbilities();
		}
	}

	// If player is trying to sprint in backwards direction
	if (IsSprinting && SprintACOs == 180.0f)
	{
		bSprintKeyDown = false;
		if (MovementState == EMovementState::STANDING)
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}

	CheckIdle();
}

//Sprint Camera Shake
void AC_PlayerCharacter::PlaySprintCameraShake()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		PlayerController->ClientPlayCameraShake(SprintCameraShake);
	}
}

//Decrease Stamina
void AC_PlayerCharacter::DecreaseStamina()
{
	if (bSprintKeyDown && MovementState == EMovementState::STANDING && PlayersVelocityMagnitude > 601.0f)
	{
		Stamina -= SprintDrain;
	}
}

// Dash
void AC_PlayerCharacter::Dash()
{
	if(IsDashUnlocked)
	{
		CheckIdle();

		//Idle Dash
		if (GetCharacterMovement()->IsWalking() == true && Stamina >= 10 && bCanDash && bIsIdle && !CrouchKeydown)
		{
			GetCharacterMovement()->bUseSeparateBrakingFriction = 0.0f;
			LaunchCharacter(FVector(CameraComp->GetForwardVector().X, CameraComp->GetForwardVector().Y, 0).GetSafeNormal() * DashDistance, true, true);
			bCanDash = false;
			Stamina -= 10.0f;
			GetWorldTimerManager().SetTimer(DashHandle, this, &AC_PlayerCharacter::StopDashing, DashStop, false);
		}

		//Moving Dash
		if (GetCharacterMovement()->IsWalking() == true && Stamina >= 10 && bCanDash && !CrouchKeydown)
		{
			GetCharacterMovement()->bUseSeparateBrakingFriction = 0.0f;
			FVector LocVelocity = GetVelocity();
			FVector NormLocVelocity = LocVelocity.GetSafeNormal();
			LaunchCharacter(NormLocVelocity * 5000.0f, false, false);
			bCanDash = false;
			Stamina -= 10.0f;
			GetWorldTimerManager().SetTimer(DashHandle, this, &AC_PlayerCharacter::StopDashing, DashStop, false);
		}

		//In Air Dash
		if (GetCharacterMovement()->IsFalling() == true && Stamina >= 10 && bCanDash && !CrouchKeydown)
		{
			GetCharacterMovement()->bUseSeparateBrakingFriction = 0.0f;
			LaunchCharacter(FVector(CameraComp->GetForwardVector().X, CameraComp->GetForwardVector().Y, 0).GetSafeNormal() * DashDistance, true, true);
			bCanDash = false;
			Stamina -= 10.0f;
			GetWorldTimerManager().SetTimer(DashHandle, this, &AC_PlayerCharacter::StopDashing, DashStop, false);
		}
	}
}

// Stop Dashing
void AC_PlayerCharacter::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(DashStopHandle, this, &AC_PlayerCharacter::ResetDash, DashCoolDown, false);
	//GetCharacterMovement()->BrakingFrictionFactor = 2.0f;

	if (CombatState == ECombatState::MELEE)
	{
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 225.0f;
	}
}

// Reset Dash
void AC_PlayerCharacter::ResetDash()
{
	bCanDash = true;
}

// Crouch
void AC_PlayerCharacter::CustomCrouch()
{
	if (bCanCrouch && bIsCrouchUnlocked)
	{
		CrouchKeydown = true;
		if (MovementState == EMovementState::STANDING)
		{
			if (bSprintKeyDown && bCanSlide)
			{
				MovementState = EMovementState::SLIDING;
				UpdateMovement();
			}

			if (!bSprintKeyDown)
			{
				MovementState = EMovementState::CROUCHING;
				UpdateMovement();

				CrouchCrossbowTransform();;

				for(auto C : Crossbow.CrossbowObject->BoltsArray)
				{
					float G = C->GetDefaultObject<AC_Crossbowbolt>()->DefaultGravity;
					float V = C->GetDefaultObject<AC_Crossbowbolt>()->DefaultVelocity;

					C->GetDefaultObject<AC_Crossbowbolt>()->SetGravity(G * 0.5f);
					C->GetDefaultObject<AC_Crossbowbolt>()->SetVelocity(V * 1.5f);
				}
			}
		}

		if (FCrouchCurve)
		{
			CrouchTimeline->Play();
		}
	}
}

// Stop Crouch
void AC_PlayerCharacter::StopCustomCrouch()
{
	CrouchKeydown = false;
	if(MovementState == EMovementState::CROUCHING)
	{
		MovementState = EMovementState::STANDING;
		UpdateMovement();

		CrouchCrossbowTransform();

		for (auto C : Crossbow.CrossbowObject->BoltsArray)
		{
			float G = C->GetDefaultObject<AC_Crossbowbolt>()->DefaultGravity;
			float V = C->GetDefaultObject<AC_Crossbowbolt>()->DefaultVelocity;

			C->GetDefaultObject<AC_Crossbowbolt>()->SetGravity(G / 0.5f);
			C->GetDefaultObject<AC_Crossbowbolt>()->SetVelocity(V / 1.5f);
		}
	}

	if (FCrouchCurve)
	{
		CrouchTimeline->Reverse();
	}

}

// Reset Crouch 
void AC_PlayerCharacter::ResetCrouch()
{
	bCanCrouch = true;
}

// Crouch Timeline Update
void AC_PlayerCharacter::CrouchTimelineFloatReturn(float Value)
{
	float x = CameraComp->GetRelativeLocation().X;
	float y = CameraComp->GetRelativeLocation().Y;

	// Smoothly transitions between Camera heights
	CameraComp->SetRelativeLocation(FVector(x, y, (FMath::Lerp(DefaultCameraHeight, CrouchedCameraHeight, Value))));

	// Smoothly transitions between capsule heights
	GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::Lerp(DefaultCapsuleHeight, CrouchedCapsuleHeight, Value));

	MeshX = GetMesh()->GetRelativeLocation().X;
	MeshY = GetMesh()->GetRelativeLocation().Y;

	GetMesh()->SetRelativeLocation(FVector(MeshX, MeshY, (FMath::Lerp(DefaultMeshHeight, CrouchedMeshHeight, Value))));
}

// Slide
void AC_PlayerCharacter::Slide()
{
	if(bIsSlideUnlocked)
	{
		FVector Velocity = GetVelocity();
		Velocity.Normalize();
		SlideDirection = Velocity;

		float SlideDirectionDotProduct = SlideDirection.DotProduct(SlideDirection, GetActorForwardVector());
		float SlideACOs = UKismetMathLibrary::DegAcos(SlideDirectionDotProduct);

		if (bCanSlide && SlideACOs < 100.0f)
		{
			bCanCrouch = false;
			bCanDash = false;
			SlideTimeline->PlayFromStart();
		}
	}
}

// Reset Slide 
void AC_PlayerCharacter::ResetSlide()
{
	bCanSlide = true;
}

// Slide Timeline Update
void AC_PlayerCharacter::SlideTimelineFloatReturn(float Value)
{
	AddActorWorldOffset(SlideDirection * (Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 2000.0f));
}

// Slide Timeline Finished
void AC_PlayerCharacter::OnSlideTimelineFinished()
{
	ResolveMovement();
	bCanSlide = false;
	bCanDash = true;
	GetWorldTimerManager().SetTimer(CrouchDelayTimerHandle, this, &AC_PlayerCharacter::ResetCrouch, 0.1f, false);

	GetWorldTimerManager().SetTimer(SlideDelayTimerHandle, this, &AC_PlayerCharacter::ResetSlide, 3.0f, false);
}

// Swimming Timeline Update
void AC_PlayerCharacter::SwimTimelineFloatReturn(float Value)
{
	MeshX = GetMesh()->GetRelativeLocation().X;
	MeshY = GetMesh()->GetRelativeLocation().Y;
	GetMesh()->SetRelativeLocation(FVector(MeshX, MeshY, (FMath::Lerp(DefaultMeshHeight, SwimMeshHeight, Value))));
}

//Swimming MeshHeight
void AC_PlayerCharacter::CheckSwimmingMeshHeight()
{
	if (MovementState == EMovementState::SWIMMING)
	{
		if (PlayersVelocityMagnitude < 10.0f)
		{
			if (FSwimCurve)
			{
				SwimTimeLine->Play();
			}
		}

		if (PlayersVelocityMagnitude >= 10.0f)
		{
			if (FSwimCurve)
			{
				SwimTimeLine->Reverse();
			}
		}
	}
}

//Stop Swimming
void AC_PlayerCharacter::StopSwimming()
{
	//Resolves the rotation of the player after they come from the water 
	if (MovementState != EMovementState::SWIMMING)
	{
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 540.0f);
		UE_LOG(LogTemp, Log, TEXT("! Swimming anymore"));
		bCanJump = true;
		bCanSlide = true;
		bCanCrouch = true;
		bCanSprint = true;
		bCanDash = true;
		//UE_LOG(LogTemp, Log, TEXT("Not Swimming"));
		//float RotYaw = GetActorRotation().Yaw;
		//SetActorRotation(FRotator(0.0f,0.0f, RotYaw));
	}
}

// Resolve Movement
void AC_PlayerCharacter::ResolveMovement()
{
	if (CrouchKeydown)
	{
		MovementState = EMovementState::CROUCHING;
		UpdateMovement();
	}

	if (!CrouchKeydown)
	{
		MovementState = EMovementState::STANDING;
		UpdateMovement();
	}
}

// Update Movement
void AC_PlayerCharacter::UpdateMovement()
{
	if (MovementState == EMovementState::STANDING)
	{
		bIsSliding = false;
		bCanJump = true;
		bCanWalk = true;

		//bCanSlide = true; // Causes weird bug where if crouch resets slide
		bCanCrouch = true;
		bCanSprint = true;
		bCanDash = true;
		StopCustomCrouch();
		if (bSprintKeyDown)
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
		}

		if (!bSprintKeyDown)
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}


	if (MovementState == EMovementState::CROUCHING)
	{
		CustomCrouch();
		bIsSliding = false;
		bCanJump = false;
		GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	}


	if (MovementState == EMovementState::SLIDING)
	{
		CustomCrouch();
		bIsSliding = true;
		bCanJump = false;
		Slide();
	}

	if (MovementState == EMovementState::SWIMMING)
	{
		GetCharacterMovement()->RotationRate = FRotator(540.0f, 540.0f, 540.0f);
		bCanJump = false;
		CrouchKeydown = false;
		bCanSlide = false;
		bCanCrouch = false;
		bCanSprint = false;
		bCanDash = false;
	}

	if (MovementState == EMovementState::NONE)
	{
		bCanWalk = false;
		bCanJump = false;
		CrouchKeydown = false;
		bCanSlide = false;
		bCanCrouch = false;
		bCanSprint = false;
		bCanDash = false;
	}

	if (MovementState == EMovementState::PUSHING)
	{
		bCanWalk = true;
		bCanJump = true;
		CrouchKeydown = false;
		bCanSlide = false;
		bCanCrouch = false;
		bCanSprint = false;
		IsSprinting = false;
		bCanDash = false;
	}
}

// EXIT AREA 

// Exit Area
void AC_PlayerCharacter::ExitArea()
{
	bEKeyPressed = true;
	if(bCanExit)
	{
		bCanExit = false;
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if(PlayerHUD)
		{
			PlayerHUD->PlayExitAreaAnimationHUD();
			PlayerHUD->MakeEKeyHintInVisible();

			GetWorldTimerManager().SetTimer(ExitAreaHandle, this, &AC_PlayerCharacter::ExitAreaFixMovement, 2.0f, false);

			GetCharacterMovement()->StopMovementImmediately();
			GetCharacterMovement()->DisableMovement();
		}
	}

	else if(bCanOpenChest)
	{
		//If player opens chest turn off hint
		//AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->MakeEKeyHintInVisible();
		bCanOpenChest = false;
	}

	else if (bCanPullLever)
	{
		//AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->MakeEKeyHintInVisible();
		bCanPullLever = false;
	}

	else if(bCanRotatePuzzle)
	{
		bCanRotatePuzzle = true;
	}

	// else if doesnt work here
	/*if(bCanInteractWithAI)
	{
		//UE_LOG(LogTemp, Log, TEXT("Hide"));
		HUD->MakeEKeyHintInVisible();
		bCanInteractWithAI = false;
	}*/

	//UE_LOG(LogTemp, Log, TEXT("e key Hide"));
}

// Exit Area Fix Movement
void AC_PlayerCharacter::ExitAreaFixMovement()
{
	ResolveMovement();
	MovementState = EMovementState::STANDING;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


// Exit Area Released 
void AC_PlayerCharacter::ExitAreaReleased()
{
	bEKeyPressed = false;
}

// Exit Area Set Can Exit
void AC_PlayerCharacter::SetCanExit()
{
	bCanExit = true;
}

// COMBAT

// Damage Over Time
void AC_PlayerCharacter::DamageOverTime()
{
	Health -= 10.0f;
	GetWorldTimerManager().SetTimer(DamageOverTimeHandle, this, &AC_PlayerCharacter::DamageOverTime, 1.0f, true);
	
	UE_LOG(LogTemp, Log, TEXT("Health is: %f"), Health);

	if(Health  <= 0.0f)
	{
		StopDamageOverTime();
		UE_LOG(LogTemp, Error, TEXT("Player has DIED"));
	}
}

// Stop Damage Over time
void AC_PlayerCharacter::StopDamageOverTime()
{
	GetWorldTimerManager().ClearTimer(DamageOverTimeHandle);
}

//Combat State
void AC_PlayerCharacter::UpdateCombatState()
{
	if (CombatState == ECombatState::UNARMED)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;
		RemoveMagicEffects();
		RemoveSS();
		DestroyCrossbowBoltTracker();
		MakeCrossbowInVisible();
		DespawnDummyBolt();
		ResetMeleeCamera();
		bCanCrouch = true;

		if (FlareBoltIndicator)
		{
			FlareBoltIndicator->Destroy();
		}
	}

	else if (CombatState == ECombatState::MELEE)
	{
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 225.0f;
		RemoveMagicEffects();
		AddSS();
		DestroyCrossbowBoltTracker();
		MakeCrossbowInVisible();
		DespawnDummyBolt();
		SetMeleeCamera();
		CrouchKeydown = false;
		bCanCrouch = false;

		if (FlareBoltIndicator)
		{
			FlareBoltIndicator->Destroy();
		}
	}

	else if (CombatState == ECombatState::RANGED)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;
		RemoveMagicEffects();
		RemoveSS(); // Access violation reading location
		MakeCrossbowVisible();

		if ((Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0))
		{
			SpawnDummyBolt();
		}

		ShouldSpawnFlareBoltIndicator();

		CreateCrossbowBoltTracker();
		ResetMeleeCamera();
		bCanCrouch = true;

		EnteredRangedState.Broadcast();
	}

	else if (CombatState == ECombatState::MAGIC)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;
		AddMagicEffects();
		RemoveSS();
		DestroyCrossbowBoltTracker();
		MakeCrossbowInVisible();
		DespawnDummyBolt();
		ResetMeleeCamera();
		CrouchKeydown = false;
		bCanCrouch = false;

		EnteredMagicState.Broadcast();

		if (FlareBoltIndicator)
		{
			FlareBoltIndicator->Destroy();
		}
	}
}

//WeaponWheel
void AC_PlayerCharacter::ShowWeaponWheel()
{
	// Flip flop node

	if(!bDisableWeaponWheel)
	{
		while (1)
		{
			if (bShowWeaponWheel)
			{
				bShowWeaponWheel = false;
				HUD->MakeWeaponWheelVisible();
				DisableCurrentCombatState.Broadcast();
				break;
			}

			else
			{
				bShowWeaponWheel = true;
				HUD->MakeWeaponWheelInVisible();
				break;
			}
		}
	}
}

// MAGIC 

// Update Ability Type
void AC_PlayerCharacter::UpdateAbility()
{
	if (CombatState == ECombatState::MAGIC && !IsSprinting)
	{
		// Ability 0
		if (AbilityType == EAbilityType::NONE)
		{
			UE_LOG(LogTemp, Log, TEXT("NONE"));
		}

		// Ability 1
		if (AbilityType == EAbilityType::ABILITY1)
		{
			if(bCanUseAbility1 && Magic >= Ability1DrainAmount && !bIsUsingAbility2)
			{
				bCanUseAbility2 = false;
				bCanUseAbility3 = false;
				bCanUseAbility4 = false;
				bIsUsingAbility1 = true;

				

				FlamesStartSoundComp = UGameplayStatics::SpawnSoundAttached(FlamesStartSound, GetMesh(), FName(""), FVector(), EAttachLocation::SnapToTarget, true);
				GetWorldTimerManager().SetTimer(StartFlamesLoopSoundHandle, this, &AC_PlayerCharacter::StartFlameLoopSound, 1.75f, false);

				ShowAbility1Effect();

				//GetWorldTimerManager().ClearTimer(FlamesFadeOutHandle);

				MaterialFadeTimeline->Stop();
				DespawnFlamesParticles();

				SpawnFlameParticles();

				//Will apply damage via Ability1Damage() every 0.01 seconds
				GetWorld()->GetTimerManager().SetTimer(FlameHandle, this, &AC_PlayerCharacter::ApplyAbility1Damage, Ability1RateOfDamage, true);
				MagickaDrain(Ability1DrainAmount, Ability1DrainTime);

				GetWorld()->GetTimerManager().ClearTimer(FlameHandle2);

				PlayAnimMontage(Ability1Animation, 1.0f);

				if (Ability2Actor)
				{
					Ability2Actor->DeSpawnParticleEffect();
					Ability2Actor->DestroyThis();
				}
			}
		}

		// Ability 2
		if (AbilityType == EAbilityType::ABILITY2)
		{
			if(bCanUseAbility2 && Magic >= Ability2DrainAmount && !bIsUsingAbility1)
			{
				bCanUseAbility1 = false;
				bCanUseAbility3 = false;
				bCanUseAbility4 = false;
				bIsUsingAbility2 = true;

				ShowAbility2Effect();

				// Will start playing sound after 1 second
				GetWorldTimerManager().SetTimer(Ability2SoundHandle, this, &AC_PlayerCharacter::StartAbility2Sound, 1.25f, false);
			
				PlayAnimMontage(Ability2Animation, 1.0f);
				GetWorldTimerManager().ClearTimer(DestroyAbility2Handle);
				GetWorldTimerManager().SetTimer(Ability2Handle, this, &AC_PlayerCharacter::SpawnSwords, 1.2f, false);

				StopAnimMontage(Ability2EndAnimation);
			}
		}

		// Ability 3
		if (AbilityType == EAbilityType::ABILITY3)
		{
			if(bCanUseAbility3 && Magic >= Ability3DrainAmount)
			{
				bCanUseAbility1 = false;
				bCanUseAbility2 = false;
				//bCanUseAbility3 = false; 
				bCanUseAbility4 = false;
				bIsUsingAbility3 = true;

				SpawnWall();

				if (Ability2Actor)
				{
					Ability2Actor->DeSpawnParticleEffect();
					Ability2Actor->DestroyThis();
				}
			}
		}

		// Ability 4
		if (AbilityType == EAbilityType::ABILITY4)
		{
			if (bCanUseAbility4 && Magic >= Ability4DrainAmount)
			{
				bCanUseAbility1 = false;
				bCanUseAbility2 = false;
				bCanUseAbility3 = false;
				bIsUsingAbility4 = true;

				ShowAbility4Effect();

				PlayAnimMontage(Ability4Animation);

				if (Ability2Actor)
				{
					Ability2Actor->DeSpawnParticleEffect();
					Ability2Actor->DestroyThis();
				}
			}
		}
	}
}

void AC_PlayerCharacter::AddMagicEffects()
{
	FActorSpawnParameters SpawnParams;

	//Right Hand Magic Spawning
	FTransform RTransform =  GetMesh()->GetSocketTransform(RightHandSocket, ERelativeTransformSpace::RTS_World);
	FVector RSpawnLocation = RTransform.GetLocation();
	FRotator RSpawnRotation = RTransform.GetRotation().Rotator();

	RightHandMagic = GetWorld()->SpawnActor<AC_RightHandMagic>(RightHandMagicClass, RSpawnLocation, RSpawnRotation, SpawnParams);
	RightHandMagic->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandSocket);

	//Left Hand Magic Spawning
	FTransform LTransform = GetMesh()->GetSocketTransform(LeftHandSocket, ERelativeTransformSpace::RTS_World);
	FVector LSpawnLocation = LTransform.GetLocation();
	FRotator LSpawnRotation = LTransform.GetRotation().Rotator();

	LeftHandMagic = GetWorld()->SpawnActor<ALeftHandMagic>(LeftHandMagicClass, LSpawnLocation, LSpawnRotation, SpawnParams);
	LeftHandMagic->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandSocket);
}

void AC_PlayerCharacter::RemoveMagicEffects()
{
	if(RightHandMagic && LeftHandMagic)
	{
		RightHandMagic->Destroy();
		LeftHandMagic->Destroy();
	}
}

void AC_PlayerCharacter::ShowDefaultEffect()
{
	if (RightHandMagic)
	{
		ResetIdleMagicRotation();
		RightHandMagic->ShowDefaultEffect();
	}

	if (LeftHandMagic)
	{
		ResetIdleMagicRotation();
		LeftHandMagic->ShowDefaultEffect();
	}
}

void AC_PlayerCharacter::ShowAbility1Effect()
{
	if (RightHandMagic)
	{
		RotateIdleMagic();
		RightHandMagic->ShowFireEffect();
	}

	if (LeftHandMagic)
	{
		RotateIdleMagic();
		LeftHandMagic->ShowFireEffect();
	}
}

void AC_PlayerCharacter::ShowAbility2Effect()
{
	if (RightHandMagic)
	{
		ResetIdleMagicRotation();
		RightHandMagic->ShowAirEffect();
	}

	if (LeftHandMagic)
	{
		ResetIdleMagicRotation();
		LeftHandMagic->ShowAirEffect();
	}
}

void AC_PlayerCharacter::ShowAbility3Effect()
{
	if (RightHandMagic)
	{
		ResetIdleMagicRotation();
		RightHandMagic->ShowVoidEffect();
	}

	if (LeftHandMagic)
	{
		ResetIdleMagicRotation();
		LeftHandMagic->ShowVoidEffect();
	}
}

void AC_PlayerCharacter::ShowAbility4Effect()
{
	if (RightHandMagic)
	{
		ResetIdleMagicRotation();
		RightHandMagic->ShowIceEffect();
	}

	if (LeftHandMagic)
	{
		ResetIdleMagicRotation();
		LeftHandMagic->ShowIceEffect();
	}
}

//Drains Magicka by set Amount
void AC_PlayerCharacter::MagickaDrain(float Amount, float Time)
{
	Magic -= Amount;

	//UE_LOG(LogTemp, Log, TEXT("Magic is: %f"), Magic);

	FTimerDelegate MagickaDelegate;

	// Params to pass into function once it ticks
	//DrainAmount = 1.0f;

	//Binding the function with Drain Amount
	MagickaDelegate.BindUFunction(this, FName("MagickaDrain"), Amount, Time);

	//Calling MagickaDrain 
	GetWorldTimerManager().SetTimer(MagickaDrainHandle, MagickaDelegate, Time, true);
}

void AC_PlayerCharacter::ReleaseAbilities()
{
	if (AbilityType == EAbilityType::ABILITY1)
	{
		Ability1Released();
	}

	if (AbilityType == EAbilityType::ABILITY2)
	{
		Ability2Released();
	}
}

//Ability 1

void AC_PlayerCharacter::Ability1()
{
	AbilityType = EAbilityType::ABILITY1;

	//HideMagicEffects();

	UpdateAbility();
}

void AC_PlayerCharacter::Ability1Check()
{
	if (Magic < Ability1DrainAmount)
	{
		Ability1Released();
		bCanUseAbility1 = false;
	}

	else
	{
		bCanUseAbility1 = true;
	}
}

void AC_PlayerCharacter::Ability1Released()
{
	if (bCanUseAbility1 && bIsUsingAbility1)
	{
		UE_LOG(LogTemp, Log, TEXT("ABILITY 1 Released"));
		bCanUseAbility2 = true;
		bCanUseAbility3 = true;
		bCanUseAbility4 = true;
		bIsUsingAbility1 = false;

		StopFlamesSounds();

		//ShowMagicEffects();
		ShowDefaultEffect();

		//bIsAbility1 = false;

		//Clears handle so no more damage is dealt
		GetWorld()->GetTimerManager().ClearTimer(FlameHandle);
		GetWorld()->GetTimerManager().ClearTimer(MagickaDrainHandle);

		PlayFlamesMaterialFadeOut(); // causes issue where particle is invisible
		//DespawnFlamesParticles();

		StopAnimMontage(Ability1Animation);

		bCanUseAbility1 = true;
		bCanUseAbility2 = true;
	}
}

void AC_PlayerCharacter::SpawnFlameParticles()
{
	LeftHandFlamesParticle = UGameplayStatics::SpawnEmitterAttached(FlamesParticle, GetMesh(), FName("LeftParticleSocket"), FVector(0.0f), FRotator(0.0f), EAttachLocation::SnapToTargetIncludingScale);
	
	// Assigns the dynamic material to the particle system
	DynamicFlamesMaterial->SetScalarParameterValue(FName("Opacity"), 1.0f);
	LeftHandFlamesParticle->SetMaterial(2, DynamicFlamesMaterial);

	RightHandFlamesParticle = UGameplayStatics::SpawnEmitterAttached(FlamesParticle, GetMesh(), FName("RightParticleSocket"), FVector(0.0f), FRotator(0.0f), EAttachLocation::SnapToTargetIncludingScale);
	
	// Assigns the dynamic material to the particle system
	DynamicFlamesMaterial->SetScalarParameterValue(FName("Opacity"), 1.0f);
	RightHandFlamesParticle->SetMaterial(2, DynamicFlamesMaterial);
}

void AC_PlayerCharacter::PlayFlamesMaterialFadeOut()
{
	MaterialFadeTimeline->PlayFromStart();
	GetWorldTimerManager().SetTimer(FlamesFadeOutHandle, this, &AC_PlayerCharacter::DespawnFlamesParticles, 0.5f, false);

	UE_LOG(LogTemp, Warning, TEXT("FadeOut"));
}

void AC_PlayerCharacter::MaterialFadeTimelineFloatReturn(float Alpha)
{
	//Makes the glow effect fade out
	DynamicFlamesMaterial->SetScalarParameterValue(FName("Opacity"), Alpha);
}

void AC_PlayerCharacter::DespawnFlamesParticles()
{
	if(IsValid(LeftHandFlamesParticle))
	{
		LeftHandFlamesParticle->DestroyComponent();
	}

	if(IsValid(RightHandFlamesParticle))
	{
		RightHandFlamesParticle->DestroyComponent();
	}

	GetWorldTimerManager().ClearTimer(FlamesFadeOutHandle);

	UE_LOG(LogTemp, Warning, TEXT("Despawn"));
}

void AC_PlayerCharacter::RotateIdleMagic()
{
	RightHandMagic->SetActorRelativeRotation(FRotator(0.0f, 120.0f, 0.0f));
	LeftHandMagic->SetActorRelativeRotation(FRotator(0.0f, 120.0f, 0.0f));
}

void AC_PlayerCharacter::ResetIdleMagicRotation()
{
	RightHandMagic->SetActorRelativeRotation(FRotator(0.0f, -0.0f, 0.0f));
	LeftHandMagic->SetActorRelativeRotation(FRotator(0.0f, -0.0f, 0.0f));
}

TArray<FHitResult> AC_PlayerCharacter::Ability1Damage()
{
	//Fires line trace from camera 
	FVector CameraLocation = CameraComp->GetComponentLocation();

	FVector EndLocation = CameraLocation + (CameraComp->GetComponentRotation().Vector() * 500.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// AN array of possible hits 
	TArray<FHitResult> OutHits;

	// Multi line trace so that damage can be applied to AI that are behind eachother 
	GetWorld()->LineTraceMultiByChannel(OutHits, CameraLocation, EndLocation, COLLISION_ABILITY1DETECTION, CollisionParams);

	//Debug LineTrace
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::White, 2.0f, 1.0f);

	// for each AI that is hit
	for (auto& Hit : OutHits)
	{
		AC_BaseAI* BaseAIHit = Cast<AC_BaseAI>(Hit.GetActor());
		AC_RollerAI* RollerAI = Cast<AC_RollerAI>(Hit.GetActor());
		if (BaseAIHit && Hit.Component == BaseAIHit->BoxComp)
		{
			//Apply damage
			UGameplayStatics::ApplyDamage(Hit.GetActor(), Ability1DamageAmount, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
			BaseAIHit->SpawnBurningEffects();
			BaseAIHit->StopDamage();
			BaseAIHit->bHasBeenHit = true;
		}

		if(Hit.GetActor() == RollerAI)
		{
			//Apply damage
			UGameplayStatics::ApplyDamage(Hit.GetActor(), Ability1DamageAmount * 15, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
		}
	}

	return OutHits;
}

//Separate function to call Ability1Damage(), as timers work with procedures rather than functions.
void AC_PlayerCharacter::ApplyAbility1Damage()
{
	Ability1Damage();
}

void AC_PlayerCharacter::StartFlameLoopSound()
{
	FlamesStartSoundComp->FadeOut(0.5f, 0.1f, EAudioFaderCurve::Linear);
	GetWorldTimerManager().ClearTimer(StartFlamesLoopSoundHandle);

	FlamesLoopSoundComp = UGameplayStatics::SpawnSoundAttached(FlamesLoopSound, GetMesh(), FName(""), FVector(), EAttachLocation::SnapToTarget, true, 1.0f, 1.0f, 0.25f);
}

void AC_PlayerCharacter::StopFlamesSounds()
{
	if(IsValid(FlamesStartSoundComp))
	{
		FlamesStartSoundComp->FadeOut(0.5f, 0.1f, EAudioFaderCurve::Linear); // Access violation reading location
	}

	if(IsValid(FlamesLoopSoundComp))
	{
		FlamesLoopSoundComp->FadeOut(0.5f, 0.1f, EAudioFaderCurve::Linear);
	}

	if(GetWorldTimerManager().IsTimerActive(StartFlamesLoopSoundHandle))
	{
		GetWorldTimerManager().ClearTimer(StartFlamesLoopSoundHandle);
	}
}

//Ability 2

void AC_PlayerCharacter::Ability2()
{
	AbilityType = EAbilityType::ABILITY2;

	UpdateAbility();
}

void AC_PlayerCharacter::SpawnSwords()
{
	FActorSpawnParameters SpawnParams;

	//Spawn at player center
	FTransform RTransform = GetMesh()->GetSocketTransform(BackSocket, ERelativeTransformSpace::RTS_World);
	FVector RSpawnLocation = RTransform.GetLocation();

	Ability2Actor = GetWorld()->SpawnActor<AC_Ability2>(Ability2Class, RSpawnLocation, FRotator::ZeroRotator, SpawnParams);
	Ability2Actor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BackSocket);

	MagickaDrain(Ability2DrainAmount, Ability2DrainTime);
}

void AC_PlayerCharacter::Ability2Check()
{
	if (Magic <= Ability2DrainAmount)
	{
		if (!bDo)
		{
			bDo = true;
			Ability2Released();
			bCanUseAbility2 = false;
			bTest = true;
		}
	}

	else
	{
		bCanUseAbility2 = true;
		bDo = false;
		bTest = false;
	}

}

void AC_PlayerCharacter::Ability2Released()
{
	if(bCanUseAbility2 && bIsUsingAbility2)
	{
		bCanUseAbility1 = true;
		bCanUseAbility3 = true;
		bCanUseAbility4 = true;
		bIsUsingAbility2 = false;

		//ShowMagicEffects();

		StopAnimMontage(Ability2Animation);

		GetWorldTimerManager().ClearTimer(Ability2Handle);

		//Stops the magicka drain 
		GetWorld()->GetTimerManager().ClearTimer(MagickaDrainHandle);

		if (IsValid(Ability2SoundComp) && Ability2SoundComp->IsPlaying())
		{
			Ability2SoundComp->FadeOut(0.5f, 0.25f, EAudioFaderCurve::Linear);
		}

		GetWorldTimerManager().ClearTimer(Ability2SoundHandle);

		if (Ability2Actor)
		{
			Ability2Actor->ParticleFadeOut();
			GetWorldTimerManager().SetTimer(DestroyAbility2Handle, this, &AC_PlayerCharacter::DespawnSwords, 1.3f, false); //1.25f
		}

		//If not using any abilities 
		PlayAnimMontage(Ability2EndAnimation, 2.0f);
	}
	
}

void AC_PlayerCharacter::DespawnSwords()
{
	if (Ability2Actor)
	{
		// Destroys the ability2 actor
		Ability2Actor->DeSpawnParticleEffect();
	}
}

void AC_PlayerCharacter::StartAbility2Sound()
{
	Ability2SoundComp = UGameplayStatics::SpawnSoundAttached(Ability2Sound, GetMesh(), FName(""), FVector(), EAttachLocation::SnapToTarget, true);
}

//Ability 3

void AC_PlayerCharacter::Ability3()
{
	AbilityType = EAbilityType::ABILITY3;

	UpdateAbility();
}

void AC_PlayerCharacter::PlayAbility3Animation()
{
	if (bCanUseAbility3)
	{
		ShowAbility3Effect();

		PlayAnimMontage(Ability3Animation);
	}
}

void AC_PlayerCharacter::SpawnWall()
{
	GetWorldTimerManager().ClearTimer(Ability3AnimationHandle);
	
	//Initial Line trace to check if we did not hit an object in world
	FVector StartLocation = GetMesh()->GetSocketLocation(RootSocket);

	// Get the right vector of the mesh
	FRotator Rotation;
	Rotation = (GetMesh()->GetComponentRotation());
	FVector RightVector =  UKismetMathLibrary::GetRightVector(Rotation);

	WallEndLocation = StartLocation + (RightVector * 150.0f);

	FHitResult Hit; 
	FCollisionQueryParams CollisionParams; 
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, WallEndLocation, COLLISION_ABILITY3DETECTION, CollisionParams);

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartLocation, WallEndLocation, FColor::Red, 2.0f, 1.0f);

	// Second line trace to check if there are objects beneath initial line trace, so that the wall is not spawned in the air
	FVector StartLocation2 = WallEndLocation;
	FRotator Rot = StartLocation2.Rotation();

	// Line trace points down 
	FVector EndLocation2 = StartLocation2 + ((UKismetMathLibrary::GetUpVector(Rot) * -1.0f) * 15.0f);

	FHitResult Hit2;
	FCollisionQueryParams CollisionParams2;
	CollisionParams2.AddIgnoredActor(this);

	bool bHit2 = GetWorld()->LineTraceSingleByChannel(Hit2, StartLocation2, EndLocation2, COLLISION_ABILITY3DETECTION, CollisionParams2);

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartLocation2, EndLocation2, FColor::Blue, 2.0f, 1.0f);


	if(!bHit && bHit2)
	{

		PlayAbility3Animation();

		if (WallArray.Num() == 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Delete Last Element"));

			//Play effect here
			if(WallArray[0]->bHasDied == false)
			{
				WallArray[0]->PlayDeSummonEffect();
			}

			WallArray[0]->DespawnSummonEffect();
			WallArray[0]->Destroy();
			WallArray.RemoveAt(0);
		}

		if (WallArray.Num() < 3)
		{
			AC_MudWall* a = SpawnWallActor();
			WallArray.Emplace(a);
			UE_LOG(LogTemp, Log, TEXT("Spawned Wall"));
		}


		for (AC_MudWall* i : WallArray)
		{
			UE_LOG(LogTemp, Log, TEXT("Array is: %s"), *i->GetName());
		}

	}
}

AC_MudWall* AC_PlayerCharacter::SpawnWallActor()
{
	FActorSpawnParameters SpawnParams;

	//Spawn at player center
	FVector SpawnLocation = FVector(WallEndLocation.X, WallEndLocation.Y -20.0f, WallEndLocation.Z - height);

	MudWallActor = GetWorld()->SpawnActor<AC_MudWall>(MudWallClass, SpawnLocation, GetActorRotation(), SpawnParams);

	MagickaDrain(Ability3DrainAmount, 0.0f);

	MudWallActor->PlayWallAnim();

	MudWallActor->PlaySummonedSound();

	Ability3Released();

	return MudWallActor;
}

void AC_PlayerCharacter::Ability3Released()
{
	if (bCanUseAbility3 && bIsUsingAbility3)
	{
		//UE_LOG(LogTemp, Log, TEXT("ABILITY 3 Released"));
		bCanUseAbility1 = true;
		bCanUseAbility2 = true;
		bCanUseAbility4 = true;
		bIsUsingAbility3 = false;
	}
}

//Ability 4

void AC_PlayerCharacter::Ability4()
{
	AbilityType = EAbilityType::ABILITY4;
	UpdateAbility();
}

void AC_PlayerCharacter::SpawnIceSpikes(TSubclassOf<AC_IceSpike> IceSpikeClass, FVector Location)
{
	UE_LOG(LogTemp, Log, TEXT("Spawned Ice Spikes"));

	FActorSpawnParameters SpawnParams;

	IceSpike = GetWorld()->SpawnActor<AC_IceSpike>(IceSpikeClass, Location, GetControlRotation(), SpawnParams);

	IceSpikeArray.Emplace(IceSpike);
}

//Spawns three ice spikes 
void AC_PlayerCharacter::Spawn3()
{
	//Spawn middle IceSpike (1st)
	FVector Location2 = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 65.0f);
	SpawnLocation2 = Location2 + GetControlRotation().Vector() * 200.0f;
	SpawnIceSpikes(MiddleIceSpikeClass, SpawnLocation2);

	FRotator Rot = IceSpikeArray[0]->GetActorRotation();
	//Rot.Yaw += 180.0f; // alternative way of * -1 

	//Spawn right IceSpike (2nd)
	FVector x1 = IceSpikeArray[0]->GetActorLocation() + (UKismetMathLibrary::GetRightVector(Rot) * 100.0f);
	SpawnIceSpikes(RightIceSpikeClass, x1);

	//Spawn left IceSpike (3rd)
	FVector x2 = IceSpikeArray[0]->GetActorLocation() + ((UKismetMathLibrary::GetRightVector(Rot) * -1.0f) * 100.0f);
	SpawnIceSpikes(LeftIceSpikeClass, x2);

	MagickaDrain(Ability4DrainAmount, 0.0f);
}

void AC_PlayerCharacter::FireIceSpikes()
{
	UE_LOG(LogTemp, Log, TEXT("Fired Ice Spikes"));

	for (AC_IceSpike* Ice : IceSpikeArray)
	{
		Ice->Fire();
	}

	IceSpikeArray.Empty();
}

void AC_PlayerCharacter::Ability4Released()
{
	if (bCanUseAbility4 && bIsUsingAbility4)
	{
		UE_LOG(LogTemp, Log, TEXT("ABILITY 4 Released"));
		bCanUseAbility1 = true;
		bCanUseAbility2 = true;
		bCanUseAbility3 = true;
		bIsUsingAbility4 = false;
	}
}

// MELEE 

// General 

void AC_PlayerCharacter::AddSS()
{
	FActorSpawnParameters SpawnParams;

	// Right hand sword spawning
	FTransform RTransform = GetMesh()->GetSocketTransform(SS.SwordSocket, ERelativeTransformSpace::RTS_World);
	FVector RSpawnLocation = RTransform.GetLocation();
	FRotator RSpawnRotation = RTransform.GetRotation().Rotator();

	SS.Sword = GetWorld()->SpawnActor<AC_BaseSkeletalMeleeWeapon>(SS.SwordClass, RSpawnLocation, RSpawnRotation, SpawnParams);
	SS.Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SS.SwordSocket);

	

	// Left hand shield spawning
	FTransform LTransform = GetMesh()->GetSocketTransform(SS.ShieldSocket, ERelativeTransformSpace::RTS_World);
	FVector LSpawnLocation = LTransform.GetLocation();
	FRotator LSpawnRotation = LTransform.GetRotation().Rotator();

	SS.Shield = GetWorld()->SpawnActor<AC_BaseShield>(SS.ShieldClass, LSpawnLocation, LSpawnRotation, SpawnParams);
	SS.Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SS.ShieldSocket);
}

void AC_PlayerCharacter::RemoveSS()
{
	if(SS.Shield && SS.Sword)
	{
		SS.Shield->Destroy();
		SS.Sword->Destroy();
	}
}

void AC_PlayerCharacter::SetMeleeCamera()
{
	CameraComp->SetRelativeLocation(FVector(-10, -2, 20)); // x = 2.522787
}

void AC_PlayerCharacter::ResetMeleeCamera()
{
	CameraComp->SetRelativeLocation(FVector(-0.070761, -9.610645, 16.054478));
}

// Combo Attacks

void AC_PlayerCharacter::DefaultAttack()
{
	if (CombatState == ECombatState::MELEE && !SS.bIsBlocking && !IsSprinting)
	{
		if (SS.bIsAttacking)
		{
			SS.bContinueCombo = true;
			UE_LOG(LogTemp, Log, TEXT("1"));
		}

		else
		{
			SS.bIsAttacking = true;
			SelectAttackAnimation();
			UE_LOG(LogTemp, Log, TEXT("2"));
		}
	}
}

FVector AC_PlayerCharacter::GetSwordHiltSocket()
{
	FVector StartLocation = SS.Sword->MeshComp->GetSocketLocation(SS.SwordTipSocket);
	return StartLocation;
}

FVector AC_PlayerCharacter::GetSwordTipSocket()
{
	FVector EndLocation = SS.Sword->MeshComp->GetSocketLocation(SS.SwordHiltSocket);
	return EndLocation;
}

void AC_PlayerCharacter::MeleeAttackDamage(USkeletalMeshComponent* SKMesh, float Damage, bool bApplyDamageOverTime)
{
	// Get the start and end location of the sphere trace (two sockets that are the length of the sword)
	FVector StartLocation = SS.Sword->MeshComp->GetSocketLocation(SS.SwordTipSocket); // make mesh in skeletal mesh paraent public then get socket location.
	FVector EndLocation = SS.Sword->MeshComp->GetSocketLocation(SS.SwordHiltSocket);

	TArray<AActor*> ActorsIgnored;
	ActorsIgnored = {this};

	// Convert the collision type to standard collision channel
	ETraceTypeQuery Trace6 = UEngineTypes::ConvertToTraceType(ECollisionChannel::COLLISION_MELEEDETECTION);

	bHits = UKismetSystemLibrary::SphereTraceSingle(SKMesh, StartLocation, EndLocation, 15.0f, Trace6, false, ActorsIgnored,EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green);

	SS.AI = Cast<AC_BaseAI>(HitResult.GetActor());

	if(bHits && SS.AI && SS.AI->bCanBeAttacked) //Access violation reading location
	{
		SS.AI->bCanBeAttacked = false;

		UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
		SS.AI->PlayHitGrunt();
		SS.AI->PlayMeleeHitAnim();
		SS.AI->CheckForAIDeath();

		// If true will aplly dmg over time
		if(bApplyDamageOverTime)
		{
			SS.AI->StartDamageOverTime(0.05, 1.1f, 4.5f);
		}
	}
}

void AC_PlayerCharacter::Rag(USkeletalMeshComponent* SKMesh)
{
	FVector StartLocation = GetMesh()->GetSocketLocation(SS.KickSocket); 
	FVector EndLocation = (GetActorRotation().Vector().ForwardVector * 0.0f) + StartLocation;
	FVector HalfSize = FVector(50.0f);
	FRotator Orientation = FRotator::ZeroRotator;

	ETraceTypeQuery BoxTrace = UEngineTypes::ConvertToTraceType(ECollisionChannel::COLLISION_MELEEDETECTION);

	TArray<AActor*> IgnoredActors;
	IgnoredActors = { this };

	FHitResult Hit;

	bool bHit = UKismetSystemLibrary::BoxTraceSingle(SKMesh, StartLocation, EndLocation, HalfSize, Orientation, BoxTrace, false, IgnoredActors, EDrawDebugTrace::ForDuration, Hit, true, FLinearColor::Blue, FLinearColor::Black);

	SS.AI = Cast<AC_BaseAI>(Hit.GetActor());

	if (bHit && SS.AI && SS.AI->bCanBeAttacked)
	{
		SS.AI->bCanBeAttacked = false;

		UGameplayStatics::ApplyDamage(Hit.GetActor(), 0.35f, UGameplayStatics::GetPlayerController(this, 0), this, NULL);

		if (SS.AI && Hit.GetActor() == SS.AI)
		{
			// Only Peasant or Lost Adventurer AI can be ragdolled.
			AC_PeasantAI* PeasantAI = Cast<AC_PeasantAI>(SS.AI);
			AC_LostAdventurer* LAAI = Cast<AC_LostAdventurer>(SS.AI);

			if(SS.AI == PeasantAI || (SS.AI == LAAI && !LAAI->bIsCrawler))
			{
				SS.AI->ApplyRagdoll();
			}

			SS.AI->PlayHitGrunt();

			SS.AI->CheckForAIDeath();
		}
	}
}

void AC_PlayerCharacter::ResetAttackVar()
{
	// Find efficent way to cast to AI
	if(GetWorld()) // Causes crash in editor
	{
		for (TActorIterator<AC_BaseAI> It(GetWorld(), AC_BaseAI::StaticClass()); It; ++It)
		{
			SS.AI = *It;
			if (SS.AI != NULL)
			{
				SS.AIArray.Add(SS.AI);
				SS.AI->bCanBeAttacked = true;
			}
		}
	}
}

void AC_PlayerCharacter::SelectAttackAnimation()
{
	switch (SS.ComboCounter)
	{
	case 0:
		//UE_LOG(LogTemp, Log, TEXT("DefaultAttack 1 "));
		SS.ComboCounter = 1;
		PlayAnimMontage(SS.DefaultAttack1, 1.0f);
		break;

	case 1:
		//UE_LOG(LogTemp, Log, TEXT("DefaultAttack 2 "));
		SS.ComboCounter = 2;
		PlayAnimMontage(SS.DefaultAttack2, 1.0f);
		break;

	case 2:
		//UE_LOG(LogTemp, Log, TEXT("DefaultAttack 3 "));
		SS.ComboCounter = 0;
		PlayAnimMontage(SS.DefaultAttack3, 1.0f);
		break;
	}
}

void AC_PlayerCharacter::ContinueCombo()
{
	if(SS.bContinueCombo)
	{
		SS.bContinueCombo = false;
		SelectAttackAnimation();
	}
}

void AC_PlayerCharacter::ResetCombo()
{
	SS.ComboCounter = 0;
	SS.bContinueCombo = false;
	SS.bIsAttacking = false;
}

// Shield Blocking

void AC_PlayerCharacter::StartBlocking()
{
	if(CombatState == ECombatState::MELEE && SS.bCanBlock && Stamina >= 5.0f && !IsSprinting)
	{
		UE_LOG(LogTemp, Log, TEXT("Blocking"));
		SS.bIsBlocking = true;
		GetCharacterMovement()->MaxWalkSpeed = 250.0f;
		PlayAnimMontage(SS.BlockingMontage, 1.0f);
	}
}

void AC_PlayerCharacter::StopBlocking()
{
	if(CombatState == ECombatState::MELEE && SS.bCanBlock)
	{
		UE_LOG(LogTemp, Log, TEXT("Stop Blocking"));
		SS.bIsBlocking = false;
		GetCharacterMovement()->MaxWalkSpeed = 450.0f;
		StopAnimMontage(SS.BlockingMontage);
		ResetCombo();
	}
}

void AC_PlayerCharacter::BlockImpact()
{
	if (Stamina >= 5.0f)
	{
		Stamina -= 5.0f;
		APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PlayerController)
		{
			PlayerController->ClientPlayCameraShake(SS.BlockCameraShake);
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SS.ShieldHitSound, GetActorLocation());
	}
}

// Ensures that the shield does not move if the player doesnt stop blocking
// Used after the player uses an ability while blocking so they remain in blocking state, if the block button is still held
void AC_PlayerCharacter::ABPStartBlocking()
{
	if (CombatState == ECombatState::MELEE && SS.bCanBlock && Stamina >= 5.0f && !IsSprinting)
	{
		UE_LOG(LogTemp, Log, TEXT("Blocking"));
		SS.bIsBlocking = true;
		GetCharacterMovement()->MaxWalkSpeed = 250.0f;
		PlayAnimMontage(SS.BlockingMontage, 1.0f);
	}
}

void AC_PlayerCharacter::CheckBlock()
{
	if(Stamina < 5.0f)
	{
		StopBlocking();
		SS.bCanBlock = false;
	}

	else
	{
		SS.bCanBlock = true;
	}
}

// Shield Bash

void AC_PlayerCharacter::ShieldBash()
{
	if(SS.bIsBlocking && Stamina >= 5.0f && !IsSprinting && SS.bCanShieldBash)
	{
		UE_LOG(LogTemp, Log, TEXT("Shield Bash"));
		SS.bCanShieldBash = false;
		PlayAnimMontage(SS.ShieldBashMontage, 1.0f);
		Stamina -= 5.0f;

		GetWorldTimerManager().SetTimer(SS.ShieldBashHandle, this, &AC_PlayerCharacter::EnableShieldBash, 0.8f, false);
	}
}

void AC_PlayerCharacter::EnableShieldBash()
{
	SS.bCanShieldBash = true;
	GetWorldTimerManager().ClearTimer(SS.ShieldBashHandle);
}

void AC_PlayerCharacter::StaggerAI(USkeletalMeshComponent* SKMesh)
{
	// Get the start and end location of the sphere trace (two sockets that are the length of the sword)
	FVector StartLocation = SS.Shield->MeshComp->GetSocketLocation(SS.ShieldBashSocket); // make mesh in skeletal mesh paraent public then get socket location.
	FVector EndLocation = (GetActorRotation().Vector() * 0.0f) + StartLocation;

	TArray<AActor*> ActorsIgnored;
	ActorsIgnored = { this };

	// Convert the collision type to standard collision channel
	ETraceTypeQuery Trace6 = UEngineTypes::ConvertToTraceType(ECollisionChannel::COLLISION_MELEEDETECTION);

	bHits = UKismetSystemLibrary::SphereTraceSingle(SKMesh, StartLocation, EndLocation, 15.0f, Trace6, false, ActorsIgnored, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green);

	SS.AI = Cast<AC_BaseAI>(HitResult.GetActor());

	if (bHits && SS.AI && SS.AI->bCanBeAttacked && SS.AI->bCanBeShieldBashed) //Access violation reading location
	{
		SS.AI->bCanBeAttacked = false;

		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 0.05f, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
		SS.AI->PlayHitGrunt();

		if (SS.AI && HitResult.GetActor() == SS.AI)
		{
			SS.AI->CheckForAIDeath();
			SS.AI->Staggered();
			SS.AI->BecomeBlind(SS.AI->StaggeredAnimation, 2.0f);
		}
	}
}

// Thrust

void AC_PlayerCharacter::Thrust()
{
	if(Stamina >= 10.0f && CombatState == ECombatState::MELEE && !IsSprinting && SS.bCanAttack)
	{
		UE_LOG(LogTemp, Log, TEXT("Thrust"));
		SS.bCanAttack = false;
		PlayAnimMontage(SS.ThrustMontage, 1.0f);
		Stamina -= 10.0f;

		// Use delay as we want to allow default attacks to interrupt, anim montage states wouldnt work for this as the state has to be reached, can be interrupted at any time
		GetWorldTimerManager().SetTimer(SS.ThrustHandle, this, &AC_PlayerCharacter::EnableThrust, 2.2f, false);
	}
}

void AC_PlayerCharacter::EnableThrust()
{
	SS.bCanAttack = true;
	GetWorldTimerManager().ClearTimer(SS.ThrustHandle);
}

// CROSSBOW

void AC_PlayerCharacter::BasicSpawnCrossbow()
{
	FActorSpawnParameters SpawnParams;

	FTransform CrossbowTransform = GetMesh()->GetSocketTransform(Crossbow.CrossbowSocket, ERelativeTransformSpace::RTS_World);
	FVector CrossbowSpawnLocation = CrossbowTransform.GetLocation();
	FRotator CrossbowSpawnRotation = CrossbowTransform.GetRotation().Rotator();

	Crossbow.CrossbowObject = GetWorld()->SpawnActor<AC_Crossbow>(Crossbow.CrossbowClass, CrossbowSpawnLocation, CrossbowSpawnRotation, SpawnParams);
	Crossbow.CrossbowObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Crossbow.CrossbowSocket);
}

void AC_PlayerCharacter::MakeCrossbowVisible()
{
	Crossbow.CrossbowObject->SetActorHiddenInGame(false);
}

void AC_PlayerCharacter::MakeCrossbowInVisible()
{
	Crossbow.CrossbowObject->SetActorHiddenInGame(true);
}

void AC_PlayerCharacter::SpawnCrossbow()
{
	BasicSpawnCrossbow();

	//SpawnCircleIndicator(GetActorLocation());

	MakeCrossbowInVisible();

	// sets current bolt to steel bolt when crossbow is first spawned
	Crossbow.CurrentBolt = Crossbow.CrossbowObject->CrossbowboltClass;
	UE_LOG(LogTemp, Log, TEXT("Current bolt is: %s"), *Crossbow.CurrentBolt->GetName());

	Crossbow.CrossbowObject->LoadBolts();
	Crossbow.CrossbowObject->UpdateNumberofBolts(Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);

	// Ensures the crossbow is in the open state
	Crossbow.CrossbowObject->MeshComp->PlayAnimation(Crossbow.CrossbowReloadOpenMontage, false);
}

void AC_PlayerCharacter::FireCrossbow()
{
	// Ensures we can only fire when we have crossbow equipped, and its reloaded
	if (CombatState == ECombatState::RANGED && bCanFireCrossbow && !bSprintKeyDown)
	{
		// if number of bolts is valid
		if((Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts > 0))
		{
			// Destroy dummy bolt, gives allusion that the dummy bolt was fired
			Crossbow.CrossbowObject->DestroyDummyBolt();

			// Update crossbow bolt UI tracker
			Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts--;
			Crossbow.CrossbowObject->UpdateNumberofBolts(Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);

			// saves number of bolts after each shot to ensure they are updated
			Crossbow.CrossbowObject->SaveBolts();

			UE_LOG(LogTemp, Log, TEXT("Num of steel bolts is: %d"), );

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Crossbow.FireSound, GetActorLocation());

			//Plays the reload animation, only when the number of bolts is valid 
			if ((Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0))
			{
				Crossbow.CrossbowObject->MeshComp->PlayAnimation(Crossbow.CrossbowReloadMontage, false);
			}

			// set the start and end location of line trace, is used for physical materials
			FVector StartLocation = CameraComp->GetComponentLocation();
			FVector EndLocation = (CameraComp->GetComponentQuat().GetForwardVector() * 20000) + StartLocation;

			// Line trace setup
			FHitResult Hit;
			FCollisionQueryParams CollisionParams;

			// Ignored actors and allows physical materials to work with trace
			CollisionParams.AddIgnoredActor(this);
			CollisionParams.AddIgnoredActor(Crossbow.CrossbowObject->Crossbowbolt);
			CollisionParams.bTraceComplex = true;
			CollisionParams.bReturnPhysicalMaterial = true;

			// Fire trace
			bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, COLLISION_CROSSBOWBOLTDETECTION, CollisionParams);

			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.0f);

			// Spawn/Fire a bolt and disable player ability to fire another
			// using Hit.Location to get projectile to launch towards centre of screen
			Crossbow.CrossbowObject->SpawnBolt(Hit.Location);
			bCanFireCrossbow = false;

			// Cast to see if trace hit AI 
			AC_BaseAI* AI = Cast<AC_BaseAI>(Hit.GetActor());

			// Get the physical material of what the trace hit, using the hit actor's physics asset
			EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

			// In essence this checks if the trace hits the AI Mesh as the other components of the AI's mesh ignore this trace
			if (bHit)
			{
				if(Hit.GetActor() == AI)
				{
					// If we hit the head will deal bonus damage, if hit body will deal default damage
					if (SurfaceType == SurfaceType2)
					{
						Crossbow.CrossbowObject->Crossbowbolt->BoltDamage *= 2.0f;
					}
				}
			}

			SpawnDummyBolt();

			// Plays timeline that moves dummy bolt up
			ReloadCrossbow();
		}

		// If there are no bolts for current bolt, do not spawn dummy bolt
		if ((Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0))
		{
			Crossbow.CurrentDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned = false;
			DespawnDummyBolt();

			if (FlareBoltIndicator)
			{
				FlareBoltIndicator->Destroy();
			}
		}
	}
}

// This will be executed after the monatage is finished playing (in ABP)
void AC_PlayerCharacter::ReloadCrossbow()
{
	// Spawns another dummy bolt and plays timeline animation
	Crossbow.CrossbowObject->ReloadCrossbow();

	// Timer for when the player can fire the crossbow again (OnTimelineFinished)
	GetWorldTimerManager().SetTimer(Crossbow.CanFireCrossbowandle, this, &AC_PlayerCharacter::ResetCrossbowCooldown, 2.5f, false);
}

// FlareBolt Indicator 

void AC_PlayerCharacter::ShouldSpawnFlareBoltIndicator()
{
	if(Crossbow.CurrentBolt == Crossbow.CrossbowObject->BoltsArray[3] && CombatState == ECombatState::RANGED)
	{
		//SpawnCircleIndicator(GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("CurrentBolt is flare Bolt"));
	}

	else
	{
		if(FlareBoltIndicator)
		{
			FlareBoltIndicator->Destroy();
		}
		UE_LOG(LogTemp, Log, TEXT("CurrentBolt is NOT flare Bolt"));
	}

	UE_LOG(LogTemp, Log, TEXT("CurrentBolt is NOT NOT flare Bolt"));
}

// Spawns flare bolt indicator
void AC_PlayerCharacter::SpawnCircleIndicator(FVector Location)
{
	if(Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0)
	{
		FActorSpawnParameters SpawnParams;
		FlareBoltIndicator = GetWorld()->SpawnActor<AC_SkeletalMeshActor>(FlareBoltIndicatorClass, Location, FRotator::ZeroRotator, SpawnParams);
		//FlareBoltIndicator->SetActorHiddenInGame(true);
	}
}

void AC_PlayerCharacter::AddCircleBoltIndicator()                                           
{
	if(IsValid(FlareBoltIndicator))
	{
		if (Crossbow.CurrentBolt == Crossbow.CrossbowObject->BoltsArray[3])
		{
			// set the start and end location of line trace
			FVector StartLocation = CameraComp->GetComponentLocation();
			FVector EndLocation = (CameraComp->GetComponentQuat().GetForwardVector() * 7500) + StartLocation;

			// Line trace setup
			FHitResult Hit;
			FCollisionQueryParams CollisionParams;

			// Ignored actors 
			CollisionParams.AddIgnoredActor(this);

			// Fire trace
			bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, COLLISION_CROSSBOWBOLTDETECTION, CollisionParams);

			//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Orange, false, 1.0f);

			// Will move the circle indicator actor to the line trace hit location
			if (bHit && FlareBoltIndicator != nullptr)
			{
				FlareBoltIndicator->SetActorLocation(Hit.Location);
				FlareBoltIndicator->SetActorHiddenInGame(false); // Access violation reading address
			}

			else
			{
				FlareBoltIndicator->SetActorHiddenInGame(true);
			}
		}

		else
		{
			FlareBoltIndicator->SetActorHiddenInGame(true);
		}

		//FlareBoltIndicatorCheck(); // Access violation executing location
	}
}

void AC_PlayerCharacter::FlareBoltIndicatorCheck()
{
	// Allows flare bolt indicator to tunr invisible if it is above ground.
	if(IsValid(FlareBoltIndicator) && FlareBoltIndicator->MeshComp && Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts > 0)
	{
		// Left Trace
		FVector StartLocation = FlareBoltIndicator->MeshComp->GetSocketLocation("LeftSocket");
		FRotator Rot = StartLocation.Rotation();
		FVector EndLocation = StartLocation + ((UKismetMathLibrary::GetUpVector(Rot) * -1.0f) * 15.0f);

		// Right Trace
		FVector RightStartLocation = FlareBoltIndicator->MeshComp->GetSocketLocation("RightSocket");
		FRotator RightRot = RightStartLocation.Rotation();
		FVector RightEndLocation = RightStartLocation + ((UKismetMathLibrary::GetUpVector(RightRot) * -1.0f) * 15.0f);

		// Up Trace
		FVector UpStartLocation = FlareBoltIndicator->MeshComp->GetSocketLocation("UpSocket");
		FRotator UpRot = UpStartLocation.Rotation();
		FVector UpEndLocation = UpStartLocation + ((UKismetMathLibrary::GetUpVector(UpRot) * -1.0f) * 15.0f);

		// Down Trace
		FVector DownStartLocation = FlareBoltIndicator->MeshComp->GetSocketLocation("DownSocket");
		FRotator DownRot = DownStartLocation.Rotation();
		FVector DownEndLocation = DownStartLocation + ((UKismetMathLibrary::GetUpVector(DownRot) * -1.0f) * 15.0f);

		FHitResult Hit;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bb1 = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, COLLISION_CROSSBOWBOLTDETECTION, CollisionParams);
		bool bb2 = GetWorld()->LineTraceSingleByChannel(Hit, RightStartLocation, RightEndLocation, COLLISION_CROSSBOWBOLTDETECTION, CollisionParams);
		bool bb3 = GetWorld()->LineTraceSingleByChannel(Hit, UpStartLocation, UpEndLocation, COLLISION_CROSSBOWBOLTDETECTION, CollisionParams);
		bool bb4 = GetWorld()->LineTraceSingleByChannel(Hit, DownStartLocation, DownEndLocation, COLLISION_CROSSBOWBOLTDETECTION, CollisionParams);

		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.0f);
		DrawDebugLine(GetWorld(), RightStartLocation, RightEndLocation, FColor::Green, false, 1.0f);
		DrawDebugLine(GetWorld(), UpStartLocation, UpEndLocation, FColor::Blue, false, 1.0f);
		DrawDebugLine(GetWorld(), DownStartLocation, DownEndLocation, FColor::Yellow, false, 1.0f);


		if((bb1 && bb2 && bb3) || (bb1 && bb2 && bb4) || (bb1 && bb3 && bb4) || (bb2 && bb3 && bb4))
		{
			FlareBoltIndicator->SetActorHiddenInGame(false);
		}

		else
		{
			FlareBoltIndicator->SetActorHiddenInGame(true);
		}

	}
}

// Updates the number of bolts for pickup
void AC_PlayerCharacter::UpdateNumberOfBolts(int32& Bolt)
{
	// Allows dummy bolt to be spawned (when switching), regardless if the current bolt is at 0 bolts 
	for (auto n : Crossbow.CrossbowObject->BoltsArray)
	{
		// if any bolt in the bolt array is at 0
		if (n->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0)
		{
			// ensure that when the player switches to that bolt, a dummy bolt is spawned
			n->GetDefaultObject<AC_Crossbowbolt>()->CorrespondingDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned = true;
		}
	}

	//Increments current bolt type
	Bolt++;

	// Updates bolt tracker
	Crossbow.CrossbowObject->UpdateNumberofBolts(Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);

	// Saves the new value of bolts
	Crossbow.CrossbowObject->SaveBolts();
	
}

void AC_PlayerCharacter::ResetCrossbowCooldown()
{
	bCanFireCrossbow = true;
}

void AC_PlayerCharacter::DespawnCrossbow()
{
	if(Crossbow.CrossbowObject)
	{
		Crossbow.CrossbowObject->Destroy();
	}
}

void AC_PlayerCharacter::SpawnDummyBolt()
{
	if(CombatState == ECombatState::RANGED) //&& Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0
	{
		// spawns dummy bolt
		Crossbow.CurrentDummyBolt = Crossbow.CrossbowObject->DummyBoltClass;
		Crossbow.CrossbowObject->SpawnDummybolt(Crossbow.CrossbowObject->CrossbowboltSocket, Crossbow.CurrentDummyBolt);
		UE_LOG(LogTemp, Log, TEXT("SPAWNED DUMMY BOLT!"));
	}
}

void AC_PlayerCharacter::DespawnDummyBolt()
{
	if(Crossbow.CrossbowObject && Crossbow.CrossbowObject->DummyBolt)
	{
		Crossbow.CrossbowObject->DummyBolt->Destroy();
	}
}

void AC_PlayerCharacter::MakeHandInvisible()
{
	GetMesh()->SetMaterial(13, InvisibleMaterial);
	UE_LOG(LogTemp, Log, TEXT("Made material invis"));
}

void AC_PlayerCharacter::MakeHandvisible()
{
	GetMesh()->SetMaterial(13, PlayerMaterials[13]);
	UE_LOG(LogTemp, Log, TEXT("Reset mat"));
}

// switch bolts

void AC_PlayerCharacter::SwitchBolts(int Index)
{
	// Set the current subclass to the object at the specified index in BoltsArray
	Crossbow.CurrentBolt = Crossbow.CrossbowObject->BoltsArray[Index];

	// Set the projectile class that will be spawned to the object at the specified index in BoltsArray
	Crossbow.CrossbowObject->CrossbowboltClass = Crossbow.CurrentBolt;

	ShouldSpawnFlareBoltIndicator();
}

// Evaluates the bolt that should be spawned when mouse wheel is moved up
int AC_PlayerCharacter::EvaluateNextBolt()
{
	// Increment index so next bolt is at index
	// Check the length of the boltsarray
	//Perform modulus of incremented index and length of array to point to next item in array
	Crossbow.CrossbowBoltIndex = (Crossbow.CrossbowBoltIndex += 1) % (Crossbow.CrossbowObject->BoltsArray.Num());
	return Crossbow.CrossbowBoltIndex;
}

// Evaluates the bolt that should be spawned when mouse wheel is moved down
int AC_PlayerCharacter::EvaluatePreviousBolt(int LastIndex)
{
	//Decrement index so previous bolt is at index
	int DecrementIndex = Crossbow.CrossbowBoltIndex -= 1;

	//Check if we at end of array and loop back around or select previous object in array
	Crossbow.CrossbowBoltIndex = DecrementIndex < 0 ? LastIndex : DecrementIndex;

	return  Crossbow.CrossbowBoltIndex;;
}

// switch dummy bolts

void AC_PlayerCharacter::SwitchDummyBolts(int Index)
{
	// Destroy previous dummy bolt 
	DespawnDummyBolt();

	Crossbow.CurrentDummyBolt = Crossbow.CrossbowObject->DummyBoltsArray[Index];

	Crossbow.CrossbowObject->DummyBoltClass = Crossbow.CurrentDummyBolt;

	//UE_LOG(LogTemp, Log, TEXT("Current dummy bolt is: %s"), *Crossbow.CurrentDummyBolt->GetName());

	//Spawn selected dummy bolt class, ensures that when bolt switching will not spawn dummy bolt if there are no bolts
	if(Crossbow.CurrentDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned == true && Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0)
	{
		Crossbow.CrossbowObject->SpawnDummybolt(Crossbow.CrossbowObject->CrossbowboltSocket, Crossbow.CrossbowObject->DummyBoltClass);
		UE_LOG(LogTemp, Log, TEXT("SPAWNED DUMMY BOLT!  Outta function"));
	}
}

int AC_PlayerCharacter::EvaluateNextDummyBolt()
{
	Crossbow.DummyBoltIndex = (Crossbow.DummyBoltIndex += 1) % (Crossbow.CrossbowObject->DummyBoltsArray.Num());
	return Crossbow.DummyBoltIndex;
}

int AC_PlayerCharacter::EvaluatePreviousDummyBolt(int LastIndex)
{
	int DecrementIndex = Crossbow.DummyBoltIndex -= 1;
	Crossbow.DummyBoltIndex = DecrementIndex < 0 ? LastIndex : DecrementIndex;
	return  Crossbow.DummyBoltIndex;
}

// Switch bolt icons

void AC_PlayerCharacter::SwitchBoltIcon(int Index)
{
	DestroyCrossbowBoltTracker();

	TSubclassOf<class UC_CrossBowBoltTracker> BoltIconPTR;

	BoltIconPTR = Crossbow.CrossbowObject->BoltIconArray[Index];

	Crossbow.CrossbowObject->BoltIconClass = BoltIconPTR;

	CreateCrossbowBoltTracker();
}

int AC_PlayerCharacter::EvaluateNextBoltIcon()
{
	BoltIconIndex = (BoltIconIndex += 1) % (Crossbow.CrossbowObject->BoltIconArray.Num());
	return BoltIconIndex;
}

int AC_PlayerCharacter::EvaluatePreviousBoltIcon(int LastIndex)
{
	int DecrementIndex = BoltIconIndex -= 1;
	BoltIconIndex = DecrementIndex < 0 ? LastIndex : DecrementIndex;
	return  BoltIconIndex;
}

void AC_PlayerCharacter::CreateCrossbowBoltTracker()
{
	if (Crossbow.CrossbowObject->BoltIconClass)
	{
		Crossbow.CrossbowObject->BoltIcon = CreateWidget<UC_CrossBowBoltTracker>(GetWorld(), Crossbow.CrossbowObject->BoltIconClass);
		if (Crossbow.CrossbowObject->BoltIcon)
		{
			Crossbow.CrossbowObject->BoltIcon->AddToViewport();
		}
	}
}

void AC_PlayerCharacter::DestroyCrossbowBoltTracker()
{
	if(Crossbow.CrossbowObject->BoltIcon)
	{
		Crossbow.CrossbowObject->BoltIcon->RemoveFromParent();
	}
}

// Aiming

void AC_PlayerCharacter::AimCrossbow()
{
	if(CombatState == ECombatState::RANGED)
	{
		bAim = true;

		//Spawn selected dummy bolt class, error is 0 bolts
		if (Crossbow.CurrentDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned == true && Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0)
		{
			GetWorldTimerManager().SetTimer(SpawnHandle, this, &AC_PlayerCharacter::SpawnDummyBoltForAiming, 0.1f, false);
			UE_LOG(LogTemp, Log, TEXT("SPAWNED DUMMY BOLT!  Outta function 2"));
		}

		Crossbow.ZoomInTimelineComp->PlayFromStart();

		CrouchCrossbowTransform();
	}
}

void AC_PlayerCharacter::SpawnDummyBoltForAiming()
{
	// Despawns and spawns new dummy bolt to ensure that its in correct location, as socket moves when aiming
	DespawnDummyBolt();

	if (Crossbow.CurrentDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned == true && Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0)
	{
		Crossbow.CrossbowObject->SpawnDummybolt(Crossbow.CrossbowObject->CrossbowboltSocket, Crossbow.CrossbowObject->DummyBoltClass);
	}

	GetWorldTimerManager().ClearTimer(SpawnHandle);
}

void AC_PlayerCharacter::StopAimCrossbow()
{
	bAim = false;
	ResetCrossbowTransform(Crossbow.CrossbowSocket);

	GetWorldTimerManager().ClearTimer(SpawnHandle);

	// Despawns and spawns new dummy bolt to ensure that its original location, prior to aiming
	DespawnDummyBolt();

	//Spawn selected dummy bolt class, error is 0 bolts
	if(Crossbow.CurrentDummyBolt && Crossbow.CurrentBolt && Crossbow.CrossbowObject)
	{
		if (Crossbow.CurrentDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned == true && Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts != 0 && CombatState == ECombatState::RANGED)
		{
			Crossbow.CrossbowObject->SpawnDummybolt(Crossbow.CrossbowObject->CrossbowboltSocket, Crossbow.CrossbowObject->DummyBoltClass);

			UE_LOG(LogTemp, Log, TEXT("SPAWNED DUMMY BOLT!  Outta function  3"));
		}
	}

	Crossbow.ZoomInTimelineComp->Reverse();

	CrouchCrossbowTransform();
}

void AC_PlayerCharacter::ChangeCrossbowTransform(FName Socket)
{
	FTransform CrossbowAimingTransform = GetMesh()->GetSocketTransform(Socket, ERelativeTransformSpace::RTS_World);
	FVector CrossbowAimingLocation = CrossbowAimingTransform.GetLocation();
	FRotator CrossbowAimingRotation = CrossbowAimingTransform.GetRotation().Rotator();

	Crossbow.CrossbowObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
	Crossbow.CrossbowObject->SetActorTransform(CrossbowAimingTransform);
}

void AC_PlayerCharacter::ResetCrossbowTransform(FName Socket)
{

	FTransform CrossbowTransform = GetMesh()->GetSocketTransform(Crossbow.CrossbowSocket, ERelativeTransformSpace::RTS_World);
	FVector CrossbowSpawnLocation = CrossbowTransform.GetLocation();
	FRotator CrossbowSpawnRotation = CrossbowTransform.GetRotation().Rotator();

	Crossbow.CrossbowObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Crossbow.CrossbowSocket);
	Crossbow.CrossbowObject->SetActorTransform(CrossbowTransform);
}

// Smoothly interploates between zoomed FOV and the default FOV
void AC_PlayerCharacter::ZoomInTimelineFloatReturn(float Delta)
{
	CameraComp->SetFieldOfView(Delta);
}

void AC_PlayerCharacter::CrouchCrossbowTransform()
{
	if(CombatState == ECombatState::RANGED && bAim)
	{
		if (CrouchKeydown)
		{
			ChangeCrossbowTransform(Crossbow.CrossbowCrouchedAimingSocket);
			MakePlayerInvisible();
			UE_LOG(LogTemp, Warning, TEXT("Crouching"));
		}

		else
		{
			ChangeCrossbowTransform(Crossbow.CrossbowAimingSocket);
			MakePlayerVisible();
			UE_LOG(LogTemp, Warning, TEXT(" NOT Crouching"));
		}

		MakeHandInvisible();
	}
	else
	{
		MakePlayerVisible();
		GetWorldTimerManager().SetTimer(InvisibleHandHandle, this, &AC_PlayerCharacter::MakeHandvisible, 0.75f, false);
	}
}

// SWAP TIME
void AC_PlayerCharacter::SwapTime()
{
	while(1)
	{
		if (ChooseA)
		{
			UE_LOG(LogTemp, Error, TEXT("FLIP"));
			SwapTimeManager->SetManagerFuture();
			MoveableObjectManager->EnableConstraints();
			ChooseA = false;
			break;
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("FLOP"));
			SwapTimeManager->SetManagerPast();
			MoveableObjectManager->EnableConstraints();
			ChooseA = true;
			break;
		}
	}
}

// AI Health Bar Detection

UPrimitiveComponent* AC_PlayerCharacter::HitComp()
{
	//Fires the line trace from the camera location
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector EndLocation = CameraLocation + (CameraRotation.Vector() * 2000.0f);

	FHitResult Hit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, EndLocation, COLLISION_AIHEALTHDETECTION, CollisionParams);

	//Debug LineTrace
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::Purple, 2.0f, 1.0f);

	return Hit.GetComponent();
}

AC_BaseAI* AC_PlayerCharacter::UpdateAI()
{
	HitComp();
	UPrimitiveComponent* GetHitComp = HitComp();

	//Finds all AI in the level
	UWorld* World = GetWorld();
	for (TActorIterator<AC_BaseAI> It(World, AC_BaseAI::StaticClass()); It; ++It)
	{
		// Hides AI health bar if trading
		if(!bIsTrading)
		{
			BaseAI = *It;
			if (BaseAI != NULL)
			{
				BaseAIArray.Add(BaseAI);

				// If the trace collides with the hit box
				if (GetHitComp == BaseAI->BoxComp)
				{
					//Display AI Health and Name
					HUD->SetAIName(BaseAI->AIName);
					HUD->SetAIHealth(BaseAI->HealthComp->Health);
					HUD->MakeAIHealthBarVisible();
					//Allows this to work for instances
					return BaseAI;
				}

				else
				{
					HUD->SetAIName("");
					HUD->MakeAIHealthBarInVisible();
				}
			}
		}

		else
		{
			HUD->SetAIName("");
			HUD->MakeAIHealthBarInVisible();
		}
	}

	return NULL;
}

// WATER VOLUME
void AC_PlayerCharacter::WaterVolumeCheck()
{
	if (bInWaterVolume && MovementState == EMovementState::STANDING)
	{
		MovementState = EMovementState::SWIMMING;
	}
}

// Camera Lock Pitch
void AC_PlayerCharacter::Pitch(float val)
{
	if (!bLockCamera)
	{
		AddControllerPitchInput(val);
	}
}

// Camera Lock Yaw
void AC_PlayerCharacter::Yaw(float val)
{
	if (!bLockCamera)
	{
		AddControllerYawInput(val);
	}
}

// INTERACT

// CLEAN UP REQUIRED
void AC_PlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	BaseAI = Cast<AC_BaseAI>(OtherActor);

	AC_Pickup* Pickup = Cast<AC_Pickup>(OtherActor);

	AC_SkeletalPickupBase* BasePickup = Cast<AC_SkeletalPickupBase>(OtherActor);

	// Checks if Actor is interactable
	if (OtherActor->GetClass()->ImplementsInterface(UC_InteractInterface::StaticClass()) && bCanInteract)
	{
		// Stops the key hint disappearing if the player overlaps with mesh of AI
		if (OtherActor != BaseAI || OtherActor == BaseAI && OtherComp == BaseAI->BoxComp) // OtherComp != BaseAI MeshComp ???
		{
			IC_InteractInterface::Execute_DisplayKeyHint(OtherActor);
		}

		// If pickup will call interact function. (use polymorpheism)
		if (OtherActor == BasePickup) 
		{
			IC_InteractInterface::Execute_Interact(OtherActor);
			UE_LOG(LogTemp, Log, TEXT("Player: PICKUP"));
		}
	}
}

// CLEAN UP REQUIRED
void AC_PlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BaseAI = Cast<AC_BaseAI>(OtherActor);

	// Checks if Actor is interactable
	if (OtherActor->GetClass()->ImplementsInterface(UC_InteractInterface::StaticClass()) && bCanInteract)
	{
		// Makes the key hint disappear
		if (OtherActor != BaseAI || OtherActor == BaseAI && OtherComp == BaseAI->BoxComp)
		{
			IC_InteractInterface::Execute_RemoveKeyHint(OtherActor);
		}
	}
}

void AC_PlayerCharacter::Interact()
{
	// Line trace setup
	FVector StartLoc;
	FVector EndLoc;

	FVector PlayerEyesLoc;
	FRotator PlayerEyesRot;

	GetActorEyesViewPoint(PlayerEyesLoc, PlayerEyesRot);

	StartLoc = PlayerEyesLoc;
	EndLoc = PlayerEyesLoc + (PlayerEyesRot.Vector() * 500.0f);

	FCollisionQueryParams TraceParams(FName(TEXT("InterfaceTrace")), true, this);

	FHitResult InteractHit = FHitResult(ForceInit);

	// Fires a line trace
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(InteractHit, StartLoc, EndLoc, COLLISION_INTERACTDETECTION, TraceParams);

	// Debug trace
	DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Green, false, 5.0f);

	// If successfully collided with an object
	if (bIsHit)
	{
		//UE_LOG(LogTemp, Log, TEXT("HIT A: %s"), *InteractHit.GetActor()->GetName());

		InteractHitActor = InteractHit.GetActor();

		// If the hit object inherits from the interact interface
		if (InteractHit.GetActor()->GetClass()->ImplementsInterface(UC_InteractInterface::StaticClass()) && bCanInteract)
		{
			// Calls the Interact function on that object
			IC_InteractInterface::Execute_Interact(InteractHit.GetActor());
		}
	}
}

// Broadcasts the signal for can trade delegate
void AC_PlayerCharacter::BroadcastCanTrade()
{
	CanTrade.Broadcast(1);
}

// DAMAGE

void AC_PlayerCharacter::ApplyDamageToPlayer(float DamageAmount)
{
	TakeDamage();

	// If Player is blocking take 50% less damage
	if(SS.bIsBlocking)
	{
		Health -= DamageAmount / 2.0f;
		BlockImpact();
	}

	else
	{
		Health -= DamageAmount;
	}

	CheckForPlayerDeath();
}

void AC_PlayerCharacter::TakeDamage()
{
	if(Health != 0.0f)
	{
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PlayerHitSound, GetActorLocation());

		if (PlayerHUD)
		{
			// clears and restarts timer so that only one fade in and fade out animation are played.
			PlayerHUD->ClearPickupTimer(0.5f);

			PlayerHUD->CreatePickupWidget(0.5f);
			PlayerHUD->DisplayDamageImage();
		}
	}
}

void AC_PlayerCharacter::CheckForPlayerDeath()
{
	if(Health <= 0.0f)
	{
		PlayerDeath();
		bDead = true;
	}
}

void AC_PlayerCharacter::PlayerDeath()
{
	bLockCamera = true;

	DisablePlayerInput();

	PlayAnimMontage(PlayerDeathMontage, 1.0f);

	// create play death screen
	AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
	PlayerHUD->CreatePlayerDeathWidget();

	// After 2.75 seconds the player can press any key to respawn
	GetWorldTimerManager().SetTimer(RestartLevelHandle, this, &AC_PlayerCharacter::EnableRespawn, 2.75f, false);
}

void AC_PlayerCharacter::EnableRespawn()
{
	// This variable allows the any key input to be enabled
	EnablePlayerInput();
	bHasDied = true;
}

void AC_PlayerCharacter::Respawn()
{
	// ensures that this input is only executed once player has died
	if(bHasDied)
	{
		// Restarts current level and resets stats
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

		// ensures input is disabled again
		bHasDied = false;
	}
}

// GENERAL

void AC_PlayerCharacter::MakePlayerInvisible()
{
	for (int i = 0; i < GetMesh()->GetMaterials().Num(); i++)
	{
		GetMesh()->SetMaterial(i, InvisibleMaterial);
	}
}

void AC_PlayerCharacter::MakePlayerVisible()
{
	GetMesh()->SetMaterial(0, PlayerMaterials[0]);
	GetMesh()->SetMaterial(1, PlayerMaterials[1]);
	GetMesh()->SetMaterial(2, PlayerMaterials[2]);
	GetMesh()->SetMaterial(3, PlayerMaterials[3]);
	GetMesh()->SetMaterial(4, PlayerMaterials[4]);
	GetMesh()->SetMaterial(5, PlayerMaterials[5]);
	GetMesh()->SetMaterial(6, PlayerMaterials[6]);
	GetMesh()->SetMaterial(7, PlayerMaterials[7]);
	GetMesh()->SetMaterial(8, PlayerMaterials[8]);
	GetMesh()->SetMaterial(9, PlayerMaterials[9]);
	GetMesh()->SetMaterial(10, PlayerMaterials[10]);
	GetMesh()->SetMaterial(11, PlayerMaterials[11]);
	GetMesh()->SetMaterial(12, PlayerMaterials[12]);
	//GetMesh()->SetMaterial(13, PlayerMaterials[13]); // new hand material
}

TArray<UMaterialInterface*> AC_PlayerCharacter::GetDefaultMaterials()
{
	return GetMesh()->GetMaterials();
}

// INPUT

void AC_PlayerCharacter::DisablePlayerInput()
{
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	DisableInput(PlayerController);
}

void AC_PlayerCharacter::EnablePlayerInput()
{
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	EnableInput(PlayerController);
}

void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// MOVING
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_PlayerCharacter::MoveRight);

	// LOOKING
	PlayerInputComponent->BindAxis("LookUp", this, &AC_PlayerCharacter::Pitch);
	PlayerInputComponent->BindAxis("LookRight", this, &AC_PlayerCharacter::Yaw);

	// JUMP
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AC_PlayerCharacter::PlayerJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AC_PlayerCharacter::StopJumping);

	// SPRINTING
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AC_PlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AC_PlayerCharacter::StopSprint);

	// DASH
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AC_PlayerCharacter::Dash);

	// Crouch
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AC_PlayerCharacter::CustomCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AC_PlayerCharacter::StopCustomCrouch);

	// Interact 
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AC_PlayerCharacter::Interact);

	// Swap Time Mechanic
	PlayerInputComponent->BindAction("SwapTime", IE_Pressed, this, &AC_PlayerCharacter::SwapTime);

	// Show Weapon Wheel
	PlayerInputComponent->BindAction("WeaponWheel", IE_Pressed, this, &AC_PlayerCharacter::ShowWeaponWheel);

	// MELEE COMBAT
	PlayerInputComponent->BindAction("DefaultAttack", IE_Pressed, this, &AC_PlayerCharacter::DefaultAttack);

	PlayerInputComponent->BindAction("Blocking", IE_Pressed, this, &AC_PlayerCharacter::StartBlocking);
	PlayerInputComponent->BindAction("Blocking", IE_Released, this, &AC_PlayerCharacter::StopBlocking);

	PlayerInputComponent->BindAction("ShieldBash", IE_Pressed, this, &AC_PlayerCharacter::ShieldBash);

	PlayerInputComponent->BindAction("Thrust", IE_Pressed, this, &AC_PlayerCharacter::Thrust);

	// MAGIC COMBAT

	// Ability 1 Input Setup
	PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &AC_PlayerCharacter::Ability1);
	PlayerInputComponent->BindAction("Ability1", IE_Released, this, &AC_PlayerCharacter::Ability1Released);

	// Ability 2 Input Setup
	PlayerInputComponent->BindAction("Ability2", IE_Pressed, this, &AC_PlayerCharacter::Ability2);
	PlayerInputComponent->BindAction("Ability2", IE_Released, this, &AC_PlayerCharacter::Ability2Released);

	// Ability 3 Input Setup
	PlayerInputComponent->BindAction("Ability3", IE_Pressed, this, &AC_PlayerCharacter::Ability3);

	// Ability 4 Input Setup
	PlayerInputComponent->BindAction("Ability4", IE_Pressed, this, &AC_PlayerCharacter::Ability4);
	PlayerInputComponent->BindAction("Ability4", IE_Released, this, &AC_PlayerCharacter::Ability4Released);

	// RANGED COMBAT

	// Crossbow fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AC_PlayerCharacter::FireCrossbow);

	// Crossbow Aim
	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &AC_PlayerCharacter::AimCrossbow);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AC_PlayerCharacter::StopAimCrossbow);

	// UI

	PlayerInputComponent->BindAction("AnyKey", IE_Pressed, this, &AC_PlayerCharacter::Respawn);

	// Settings
	PlayerInputComponent->BindAction("Settings", IE_Pressed, this, &AC_PlayerCharacter::OpenSettingsMenu).bExecuteWhenPaused = true;
}

void AC_PlayerCharacter::OpenSettingsMenu()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	while (1)
	{
		if (bOpenSettings)
		{
			UE_LOG(LogTemp, Error, TEXT("OPEN SETTINGS"));

			// Create settings menu 
			HUD->CreateSettingsWidget();
			HUD->HideAllElements();
			HUD->HideSouls();

			// UI Settings
			UGameplayStatics::SetGamePaused(this, true);
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI());

			bOpenSettings = false;
			break;
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("CLOSE SETTINGS"));

			// Destroy Settings menu 
			HUD->DestroySettingsWidget();
			HUD->ShowAllElements();
			HUD->ShowSouls();

			// UI Settings
			UGameplayStatics::SetGamePaused(this, false);
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());

			bOpenSettings = true;
			break;
		}
	}
}

void AC_PlayerCharacter::SavePlayerLocation()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->PlayerLocation = GetActorLocation();

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("LOC"), 0))
		{
			UE_LOG(LogTemp, Log, TEXT("Save Succeeded (crossbowbolts)"));
		}
	}
}

void AC_PlayerCharacter::LoadPlayerLocation()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LOC"), 0)))
	{
		SetActorLocation(LoadedGame->PlayerLocation);

		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		//UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->PlayerLocation.ToString());
	}
}

void AC_PlayerCharacter::SaveNumberOfSouls()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		// Saves the NumberOfSouls, sets the currency saved variable to the NumberOfSouls value
		SaveGameInstance->Currency = NumberOfSouls;

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SOULS"), 0))
		{
			UE_LOG(LogTemp, Log, TEXT("Save Succeeded (souls)"));
		}
	}
}

void AC_PlayerCharacter::LoadNumberOfSouls()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SOULS"), 0)))
	{
		// The operation was successful, so LoadedGame now contains the data we saved earlier.

		// Sets the NumberOfSouls to the Currency saved variable
		NumberOfSouls = LoadedGame->Currency;

		// Sends a signal to HUD widget to update text
		UpdatenumberOfSouls.Broadcast(NumberOfSouls);
	}
}

// use when updating number of bolts
void AC_PlayerCharacter::ResetBolts()
{
	// Allows dummy bolt to be spawned (when switching), regardless if the current bolt is at 0 bolts 
	for (auto n : Crossbow.CrossbowObject->BoltsArray)
	{
		// if any bolt in the bolt array is at 0
		if (n->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0)
		{
			// ensure that when the player switches to that bolt, a dummy bolt is spawned
			n->GetDefaultObject<AC_Crossbowbolt>()->CorrespondingDummyBolt->GetDefaultObject<AC_DummyBolt>()->bCanBeSpawned = true;
		}
	}

	// spawns a dummy bolt, only if there is no current dummy bolt (num of bolts is 0) ONLY WORKS IF CURRENTLY EQUIPPED BOLT IS 0
	if(Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0)
	{
		Crossbow.CurrentDummyBolt = Crossbow.CrossbowObject->DummyBoltClass;
	    Crossbow.CrossbowObject->SpawnDummybolt(Crossbow.CrossbowObject->CrossbowboltSocket, Crossbow.CurrentDummyBolt);
	}

	// Set the number of bolts to a new value
	Crossbow.CrossbowObject->ResetBolts();
	// Updates bolt tracker
	Crossbow.CrossbowObject->UpdateNumberofBolts(Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);
}

void AC_PlayerCharacter::LockedAbilities(bool bIsDashLocked, bool bIsCrouchLocked, bool bIsSlideLocked, bool bIsWeaponWheelLocked)
{
	bIsDashLocked ? IsDashUnlocked = false : IsDashUnlocked = true;

	bIsCrouchLocked ? bIsCrouchUnlocked = false : bIsCrouchUnlocked = true;

	bIsSlideLocked ? bIsSlideUnlocked = false : bIsSlideUnlocked = true;

	bIsWeaponWheelLocked ? bDisableWeaponWheel = true : bDisableWeaponWheel = false;
}

// Settings

void AC_PlayerCharacter::SetSoundVolume()
{
	// Create this widget to load the correct volumes for sound
	HUD->CreateSoundSettingsWidget();
	HUD->SoundSettingsWidget->SetVisibility(ESlateVisibility::Hidden);

	HUD->CreateVideoSettingsWidget();
	HUD->VideoSettingsWidget->SetVisibility(ESlateVisibility::Hidden);

	// detsroy it quickly later
	FTimerHandle SoundHandle;
	GetWorldTimerManager().SetTimer(SoundHandle, this, &AC_PlayerCharacter::DestroyTempSoundWidget, 0.35f, false);
}

void AC_PlayerCharacter::DestroyTempSoundWidget()
{
	HUD->DestroySoundSettingsWidget();
	HUD->DestroyVideoSettingsWidget();
}
