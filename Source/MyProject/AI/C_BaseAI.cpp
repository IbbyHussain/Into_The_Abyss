// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseAI.h"
#include "MyProject\MyProject.h"
#include "MyProject/Components/C_HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/Misc/C_Ability2.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/TransformNonVectorized.h"
#include "DestructibleComponent.h"
#include "MyProject/AI/C_BaseAIController.h"
#include "Sound/SoundBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"

#include "MyProject/Weapons/MeleeWeapons/C_BaseSkeletalMeleeWeapon.h"

#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SoulsPickup.h"

#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "Particles/ParticleSystemComponent.h"

#include "MyProject/AI/MeleeAI/C_MeleeAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"

#include "MyProject/Quest System/C_BaseQuest.h"
#include "MyProject/Components/C_POIComponent.h"

AC_BaseAI::AC_BaseAI()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(GetCapsuleComponent());
	
	HealthComp = CreateDefaultSubobject<UC_HealthComponent>(TEXT("HealthComp"));

	DestructibleMeshComp = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible mesh Comp"));
	DestructibleMeshComp->SetupAttachment(GetMesh());
	DestructibleMeshComp->SetVisibility(false);

	HipsBone = ("Hips");

	HipsSocket = ("PhySocket");

	NeckSocket = ("NeckSocket");

	Ability2DamageAmount = 0.03f;

	Ability2Rate = 0.2f;

	SnapShotName = ("Snap");

	// Frozen Montage Array

	bPlayFrozenPose = true;

	bCanBeAttacked = true;

	bCanBeShieldBashed = true;

	bShowEKeyHint = true;

	bCanTalkAI = true;

	bCanRagdoll = true;

	TimeUntilEnableMovement = 2.0f;

	// Capsule Component Settings
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	GetCapsuleComponent()->SetCapsuleRadius(45.0f);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_ABILITY1DETECTION, ECollisionResponse::ECR_Overlap);

	// Mesh Component Settings
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_ABILITY1DETECTION, ECollisionResponse::ECR_Overlap);

	GetMesh()->SetWorldLocation(FVector(0.0f, 0.0f, -100.0f));

	FRotator MeshRotation = FRotator(0.0f, -90.0f, 0.0f);
	MeshRotation.Quaternion();
	GetMesh()->SetWorldRotation(MeshRotation);

	// Destructible Mesh Component Settings

	DestructibleMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DestructibleMeshComp->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);

	// Need to do this in the editor as no support for destructible mesh collision at the momemnt
	//DestructibleMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	//DestructibleMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	// Box Component Settings

	BoxComp->SetWorldScale3D(FVector(3.5f));
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); // causes ability 2 to not work, but causes two blind bolts / explosive aoe

	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);

	TimeUntilRagdollDeath = 3.0f;

	TimeUntilDestroyed = 15.0f;

	bTakeAbility2Damage = true;

	BossDamageReduction = 0.1;
}

void AC_BaseAI::BeginPlay()
{
	Super::BeginPlay();

	// Gives us access to this delegate 
	HealthComp->OnHealthChanged.AddDynamic(this, &AC_BaseAI::UpdateHealth);

	// Ability 2 damage
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AC_BaseAI::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AC_BaseAI::OnOverlapEnd);

	FrozenMontageArray.Emplace(FrozenPose1);
	FrozenMontageArray.Emplace(FrozenPose2);
	FrozenMontageArray.Emplace(FrozenPose3);

	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	
	if (PlayerCharacter)
	{
		// DONT CAUSE CRASH
		PlayerCharacter->EnteredMagicState.AddDynamic(this, &AC_BaseAI::MagicStateCollision);
	}

	if (PlayerCharacter)
	{
		// DONT CAUSE CRASH
		PlayerCharacter->EnteredRangedState.AddDynamic(this, &AC_BaseAI::RangedStateCollision);
	}


	// Must be set in C++ as blueprints doesnt change it. Necessary for physical materials to work.
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_CROSSBOWBOLTDETECTION, ECollisionResponse::ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(COLLISION_CROSSBOWBOLTDETECTION, ECollisionResponse::ECR_Ignore);
	DestructibleMeshComp->SetCollisionResponseToChannel(COLLISION_CROSSBOWBOLTDETECTION, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_CROSSBOWBOLTDETECTION, ECollisionResponse::ECR_Block);

	// Copper Bolt collison stops components from triggering hits from multi trace
	GetMesh()->SetCollisionResponseToChannel(COLLISION_COPPERBOLTDETECTION, ECollisionResponse::ECR_Ignore);
	DestructibleMeshComp->SetCollisionResponseToChannel(COLLISION_COPPERBOLTDETECTION, ECollisionResponse::ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(COLLISION_COPPERBOLTDETECTION, ECollisionResponse::ECR_Ignore);

	// Multi trace collision settings
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore); // causes ability 2 to not work, but causes two blind bolts aoe / explosive aoe
	BoxComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);

	// Add the assigned materials to a new array
	for(int i = 0; i < GetMesh()->GetMaterials().Num(); i++) // Need to get the materials that have been assigned
	{
		DefaultMaterials.Add(GetMesh()->GetMaterials()[i]);
	}
	
	for(auto x : DefaultMaterials)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI IS: %s, there are: %d materials"), *this->GetName(), DefaultMaterials.Num());
	}
}

void AC_BaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Start Damage refers to burn damage
	if(bHasBeenHit)
	{
		StartDamage();
	}

	bIsRagdollTimerActive = GetWorldTimerManager().IsTimerActive(RagdollCooldownHandle);

	UpdateCapsule();

	if(PlayerCharacter && PlayerCharacter->bDead)
	{
		auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
		if(AIController)
		{
			UBrainComponent* LocalComp = AIController->GetBrainComponent();
			LocalComp->StopLogic(FString("Player Death"));
		}
	}
}

void AC_BaseAI::UpdateHealth(UC_HealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, 
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Health <= 0.0f && !bHasDied)
	{
		//UE_LOG(LogTemp, Log, TEXT("AI HAS DIED! 1"));
		//bHasDied = true;
		//GetWorldTimerManager().SetTimer(DeathHandle, this, &AC_BaseAI::Death, 3.2f, false);
		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AC_BaseAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Ability2 = Cast<AC_Ability2>(OtherActor);

	if (Ability2)
	{

		if (OtherActor == Ability2 && OtherComp == Ability2->BoxComp && !bInRagdoll && bTakeAbility2Damage)
		{

			bOverlapping = true;

			CheckForAIDeath();

			PlayHitGrunt();

			if (!bIsRagdollTimerActive)
			{
				StartRagdollTimer();
			}

			if (!bHasDied)
			{
				GetWorldTimerManager().SetTimer(Ability2DamageHandle, this, &AC_BaseAI::ApplyDamage2, Ability2Rate, true); // Apply damage 2
			}
		}
	}
}

void AC_BaseAI::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Ability2 = Cast<AC_Ability2>(OtherActor);

	if (Ability2)
	{
		if (OtherActor == Ability2 && OtherComp == Ability2->BoxComp)
		{
			GetWorldTimerManager().ClearTimer(RagdollHandle);
			GetWorldTimerManager().ClearTimer(Ability2DamageHandle);
			bOverlapping = false;
		}
	}
}

//Damage Over Time
void AC_BaseAI::StartDamage()
{
	HealthComp->Health -= Amount;

	CheckForAIDeath();

	TypeOfDeath = ETypeOfDeath::ABILITY1DEATH;
}

// Used when AI enters a water volume
void AC_BaseAI::StopDamage()
{
	bHasBeenHit = false;
}

FString AC_BaseAI::DisplayText(FString AIText)
{
	FString text = AIText;
	return text;
}

bool AC_BaseAI::OverlappingLeverBoxCollision()
{
	if (BoxComp->IsOverlappingActor(PlayerCharacter))
	{
		bOverlappingPlayer = true;
		return bOverlappingPlayer;
	}

	else
	{
		bOverlappingPlayer = false;
		return bOverlappingPlayer;
	}
}

void AC_BaseAI::StartRagdollTimer()
{
	if(bCanRagdoll)
	{
		GetWorldTimerManager().SetTimer(RagdollHandle, this, &AC_BaseAI::ApplyRagdoll, 3.0f, true);
	}
}

void AC_BaseAI::ApplyRagdoll()
{
	if (!bHasDied && bCanRagdoll)
	{
		EnableRagdoll();

		bInRagdoll = true;

		bCanTalkAI = false;
		bShowEKeyHint = false;

		GetWorldTimerManager().ClearTimer(RagdollHandle);

		// Starts timer to reset ragdoll.
		GetWorldTimerManager().SetTimer(RagdollResetHandle, this, &AC_BaseAI::StartDisableRagdoll, 5.0f, false);
	}
}

void AC_BaseAI::EnableRagdoll()
{
	if (bCanRagdoll)
	{
		GetMesh()->SetSimulatePhysics(true);
		bIsSimulatingPhysics = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

		// STOP the AI Behaviour tree
		auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
		UBrainComponent* LocalComp = AIController->GetBrainComponent();
		LocalComp->StopLogic(FString("Ragdoll"));

		UE_LOG(LogTemp, Error, TEXT("STOP LOGIC"));
	}
}

void AC_BaseAI::StartDisableRagdoll()
{
	CachePose();
	GetWorldTimerManager().ClearTimer(RagdollResetHandle);
	GetWorldTimerManager().SetTimer(DisableRagdollHandle, this, &AC_BaseAI::DisableRagdoll, 0.2f, false);
}

void AC_BaseAI::DisableRagdoll()
{
	if(bCanRagdoll)
	{
		GetWorldTimerManager().ClearTimer(DisableRagdollHandle);
		GetMesh()->SetSimulatePhysics(false);
		bIsSimulatingPhysics = false;
		GetMesh()->GetAnimInstance()->Montage_Play(StandUpMontage, 1.0f);
		bHasStopped = false;

		bInRagdoll = false;
		bStopRagdoll = true;
		GetWorldTimerManager().SetTimer(RagdollCooldownHandle, this, &AC_BaseAI::RagdollCooldown, 6.0f, false);

		GetWorldTimerManager().SetTimer(EnableMovementHandle, this, &AC_BaseAI::EnableMovement, TimeUntilEnableMovement, false);

		bCanTalkAI = true;
		bShowEKeyHint = true;
	}
}

void AC_BaseAI::RagdollCooldown()
{
	// Ensures that bIsRagdollTimerActive is false so no check for it is needed
	GetWorldTimerManager().ClearTimer(RagdollCooldownHandle);

	if (bOverlapping)
	{
		StartRagdollTimer();
	}

}

void AC_BaseAI::UpdateCapsule()
{
	if(bIsSimulatingPhysics)
	{
		CalculateMeshLocation();
		GetCapsuleComponent()->SetWorldLocation(MeshLocation);
	}

	else
	{
		MeshLocation = GetMesh()->GetSocketLocation(HipsSocket) + FVector(0.0f, 0.0f, 100.0f);
	}
}

void AC_BaseAI::CalculateMeshLocation()
{
	FVector StartLoc = GetMesh()->GetSocketLocation(HipsSocket);
	FVector EndLoc1 = FVector(0.0f, 0.0f, -1.0f) * 100.0f;
	FVector EndLoc =  GetMesh()->GetSocketLocation(HipsSocket) + EndLoc1;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Visibility, CollisionParams);

	if(Hit)
	{
		CapsuleLocation =  HitResult.Location + FVector(0.0f, 0.0f, 100.0f);
		MeshLocation = FMath::VInterpTo(MeshLocation, CapsuleLocation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 5.0f);
	}

	else
	{
		CapsuleLocation = GetMesh()->GetSocketLocation(HipsSocket) + FVector(0.0f, 0.0f, 100.0f);
	}
}

bool AC_BaseAI::CalculateFacingDirectionC()
{
	FVector b = UKismetMathLibrary::GetRightVector(GetMesh()->GetSocketRotation(HipsSocket));
	FVector c = FVector(0.0f, 0.0f, 1.0f);

	float a = FVector::DotProduct(b, c);

	return a >= 0.0f;
}

void AC_BaseAI::UpdateStandingOrientation()
{
	FVector NSock = GetMesh()->GetSocketLocation(NeckSocket);
	FVector HSock = GetMesh()->GetSocketLocation(HipsSocket);

	FVector ret = bIsFacingUpwards ? HSock - NSock : NSock - HSock;

	FRotator Rot =  UKismetMathLibrary::MakeRotFromZX(FVector(0.0f, 0.0f, 1.0f), ret);

	FTransform ActorTransform;
	ActorTransform.SetLocation(MeshLocation);
	ActorTransform.SetRotation(Rot.Quaternion());
	ActorTransform.SetScale3D(FVector(1.0f));
	SetActorTransform(ActorTransform);
}

void AC_BaseAI::UpdateStandingMontage()
{
	if(bIsFacingUpwards)
	{
		//UE_LOG(LogTemp, Log, TEXT("Standing Up from Back"));
	}

	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Standing Up from Stomach"));
	}

	StandUpMontage = bIsFacingUpwards ? StandUpFromBackMontage : StandUpFromStomachMontage;
}

void AC_BaseAI::CachePose()
{
	bIsFacingUpwards = CalculateFacingDirectionC();
	UpdateStandingOrientation();
	UpdateStandingMontage();
	GetWorldTimerManager().SetTimer(FrameSkipHandle, this, &AC_BaseAI::bfunction, 0.01f, false);
}

void AC_BaseAI::bfunction()
{
	GetWorldTimerManager().ClearTimer(FrameSkipHandle);
	GetMesh()->GetAnimInstance()->SavePoseSnapshot(SnapShotName);
	bHasStopped = true;
}

void AC_BaseAI::EnableMovement()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	GetMesh()->GetAnimInstance()->Montage_Stop(0.25, StandUpMontage);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	// RESTART the AI Behaviour tree
	auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
	UBrainComponent* LocalComp = AIController->GetBrainComponent();
	LocalComp->RestartLogic();

	UE_LOG(LogTemp, Error, TEXT("RESTART LOGIC"));
}

void AC_BaseAI::ApplyDamage2()
{
	if(bIsBoss)
	{
		UGameplayStatics::ApplyDamage(this, Ability2DamageAmount * BossDamageReduction, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
	}
	else
	{
		UGameplayStatics::ApplyDamage(this, Ability2DamageAmount, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
	}

	CheckForAIDeath();

	TypeOfDeath = ETypeOfDeath::ABILITY2DEATH;
}

void AC_BaseAI::PlayHitGrunt()
{
	if(!bHasDied)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitGrunt, GetActorLocation());
	}
}

void AC_BaseAI::ShouldFocusOnPlayer()
{
	// Get distance from AI to Player
	FVector AILocation = GetActorLocation();
	FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FVector Distance = AILocation - PlayerLocation;
	float Magnitude = Distance.Size();

	// if distance is less than 1000, the AI will turn to face the player
	if(Magnitude <= 1000.0f && !bIsFrozen && !bIsBlind)
	{
		UE_LOG(LogTemp, Error, TEXT("Distance was less than 200 and set new AI focus!"));
		auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
		AIController->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), EAIFocusPriority::Gameplay);
	}
}

void AC_BaseAI::CheckForAIDeath()
{
	if (HealthComp->Health <= 0.0f && !bHasDied)
	{
		StopDamage();

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);

		OnDeath();

		bCanTalkAI = false;
		bShowEKeyHint = false;

		// Stops Behavior tree Logic
		auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
		UBrainComponent* LocalComp = AIController->GetBrainComponent();
		LocalComp->StopLogic(FString("Death"));


		//Stops the AI from removing physics ( Doesnt execute RemoveRagdoll() ) This also ensures no animations are played
		GetWorldTimerManager().ClearAllTimersForObject(this);

		// Call the quest killed objective delegate
		if(BaseAIQuestRef)
		{
			BaseAIQuestRef->CheckKilledEnemyObjectiveDelegate.Broadcast(this);
		}

		// default death
		if (!bIsFrozen)
		{
			// Tells ABP to play death animation
			bHasDied = true;
			GetWorldTimerManager().SetTimer(DeathHandle, this, &AC_BaseAI::Death, TimeUntilRagdollDeath, false);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());

			TypeOfDeath = ETypeOfDeath::DEFAULTDEATH;
		}

		//If the AI is already simulating physics we dont need to simulate again or wait until Animation is done to destroy BoxComp
		else if (GetMesh()->IsSimulatingPhysics())
		{
			BoxComp->DestroyComponent();
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationCustomMode);
			GetWorldTimerManager().ClearTimer(DeathHandle);
		}

		// If AI is frozen
		else
		{
			Shatter();
		}

		GetWorldTimerManager().SetTimer(DespawnHandle, this, &AC_BaseAI::DestroyThis, TimeUntilDestroyed, false);
		
	}
}

// Used to destroy fight manager for melee AI
void AC_BaseAI::OnDeath()
{
	UE_LOG(LogTemp, Error, TEXT("AI Died, ON DEATH"));
}

// Default Death
void AC_BaseAI::Death()
{
	GetWorldTimerManager().ClearTimer(DeathHandle);

	if(bCanRagdoll)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationCustomMode);
		bInRagdoll = true;
	}

	// Spawns a soul pickup when the AI dies
	SpawnItem(TEXT("PickupSocket"), SoulsPickup, false, PickupClass);

	if(BoxComp)
	{
		BoxComp->DestroyComponent();
	}
}

void AC_BaseAI::ResetMaterials()
{
	// Reset Materials to default
	for (int i = 0; i < GetMesh()->GetMaterials().Num(); i++)
	{
		GetMesh()->SetMaterial(i, DefaultMaterials[i]);
	}
}

void AC_BaseAI::BecomeFrozen()
{
	if(bCanRagdoll)
	{
		bIsFrozen = true;

		// Stops AI movement
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();

		auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
		UBrainComponent* LocalComp = AIController->GetBrainComponent();
		LocalComp->PauseLogic(FString("Frozen"));

		// Clear focus so no longer rotates to face player
		AIController->ClearFocus(EAIFocusPriority::Gameplay);

		//abc();

		//Set materials to frozen material
		for (int i = 0; i < GetMesh()->GetMaterials().Num(); i++)
		{
			GetMesh()->SetMaterial(i, FrozenMaterial);
		}

		//Plays a random montage from the array
		if (bPlayFrozenPose)
		{
			PlayAnimMontage(FrozenMontageArray[UKismetMathLibrary::RandomInteger(3)], 1.0f);
			bPlayFrozenPose = false;
		}

		// If the AI is hit consecutively will remain frozen
		if (GetWorldTimerManager().IsTimerActive(BecomeUnFrozenHandle))
		{
			GetWorldTimerManager().ClearTimer(BecomeUnFrozenHandle);
		}

		DespawnBurningEffects();

		GetWorldTimerManager().SetTimer(BecomeUnFrozenHandle, this, &AC_BaseAI::BecomeUnFrozen, 3.0f, false);
	}
}

void AC_BaseAI::BecomeUnFrozen()
{
	bIsFrozen = false;

	bPlayFrozenPose = true;

	auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
	UBrainComponent* LocalComp = AIController->GetBrainComponent();
	LocalComp->ResumeLogic(FString("Frozen"));

	//Set materials to their defaults old way 
	/*GetMesh()->SetMaterial(0, Material0);
	GetMesh()->SetMaterial(1, Material1);
	GetMesh()->SetMaterial(2, Material2);
	GetMesh()->SetMaterial(3, Material3);
	GetMesh()->SetMaterial(4, Material4);
	GetMesh()->SetMaterial(5, Material5);
	GetMesh()->SetMaterial(6, Material6);*/

	ResetMaterials();

	//Resume anim graph and ai behaviour tree
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	// Do a for loop on the array.
	StopAnimMontage(FrozenPose1);
	StopAnimMontage(FrozenPose2);
	StopAnimMontage(FrozenPose3);

	GetWorldTimerManager().ClearTimer(BecomeUnFrozenHandle);
}

void AC_BaseAI::Shatter()
{
	//UE_LOG(LogTemp, Log, TEXT("SHATTER"));

	DestroyAIItems();

	DespawnBurningEffects();

	// Spawns a soul pickup when the AI dies
	SpawnItem(TEXT("PickupSocket"), SoulsPickup, false, PickupClass);

	//Mud wall death
	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DestructibleMeshComp->SetVisibility(true);

	// Causes mud wall to fracture into DM
	DestructibleMeshComp->ApplyRadiusDamage(20.0f, GetActorLocation(), 5.0f, 0.0f, false);

	// put in do once
	if(!bDoOnce)
	{
		bDoOnce = true;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShatteredSound, GetActorLocation(), GetActorRotation(), 1.0f);
	}

	GetWorldTimerManager().SetTimer(DestroyHandle, this, &AC_BaseAI::DestroyThis, 8.0f, false);

	if (BoxComp)
	{
		BoxComp->DestroyComponent();
	}
}

void AC_BaseAI::DestroyThis()
{
	GetWorldTimerManager().ClearTimer(DestroyHandle);

	DestroyAIItems();

	Destroy();
}

// Melee Weapon State
void AC_BaseAI::MeleeAttackDamage(USkeletalMeshComponent* SKMesh)
{
	
}

void AC_BaseAI::PlayMeleeHitAnim()
{
	PlayAnimMontage(MeleeHitMontage, 1.0f);
}

// Will spawn an actor attached to a socket with default spawn parameters
AActor* AC_BaseAI::SpawnItem(FName SocketName, AActor* Item, bool bShouldBeAttached, TSubclassOf<AActor> ItemClass)
{
	FActorSpawnParameters SpawnParams;

	FTransform ItemTransform = GetMesh()->GetSocketTransform(SocketName, ERelativeTransformSpace::RTS_World);
	FVector ItemSpawnLocation = ItemTransform.GetLocation();
	FRotator ItemSpawnRotation = ItemTransform.GetRotation().Rotator();

	Item = GetWorld()->SpawnActor<AActor>(ItemClass, ItemSpawnLocation, ItemSpawnRotation, SpawnParams);

	if(bShouldBeAttached)
	{
		Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

		return Item;
	}

	return Item;
}

void AC_BaseAI::ChangeColours(bool bRandomColours, TArray<UMaterialInstanceDynamic*> MaterialArray, int MaxArrayAmount, int MaterialIndex)
{
	if(bRandomColours)
	{
		int a = FMath::RandRange(0, MaxArrayAmount);

		GetMesh()->SetMaterial(MaterialIndex, MaterialArray[a]);
	}
}

void AC_BaseAI::BecomeBlind(UAnimMontage* MontageToPlay, float TimeUntilRecover)
{
	bIsBlind = true;

	// Stops AI movement
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
	UBrainComponent* LocalComp = AIController->GetBrainComponent();
	LocalComp->PauseLogic(FString("Blind"));

	// Clear focus so no longer rotates to face player
	AIController->ClearFocus(EAIFocusPriority::Gameplay);

	// Plays animation
	PlayAnimMontage(MontageToPlay, 1.0f);

	//Binding the function with specific values
	TimerDel.BindUFunction(this, FName("RemoveBlindness"), MontageToPlay);
	GetWorld()->GetTimerManager().SetTimer(BlindnessHandle, TimerDel, TimeUntilRecover, false);

	UE_LOG(LogTemp, Log, TEXT("Become Blind"));
}

void AC_BaseAI::RemoveBlindness(UAnimMontage* MontageToStop)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	StopAnimMontage(MontageToStop);

	auto const AIController = Cast<AAIController>(UAIBlueprintHelperLibrary::GetAIController(this));
	UBrainComponent* LocalComp = AIController->GetBrainComponent();
	LocalComp->ResumeLogic("Blind");

	GetWorldTimerManager().ClearTimer(BlindnessHandle);

	bIsBlind = false;

	UE_LOG(LogTemp, Log, TEXT("Remove Blind"));
}

// Provides immunity to AI, so that they cannot be continuously shield bashed
void AC_BaseAI::Staggered()
{
	bCanBeShieldBashed = false;
	GetWorldTimerManager().SetTimer(StaggeredHandle, this, &AC_BaseAI::RecoverFromStagger, 10.0f, false);
}

void AC_BaseAI::RecoverFromStagger()
{
	bCanBeShieldBashed = true;
	GetWorldTimerManager().ClearTimer(StaggeredHandle);
}

// Damage over time for this class
void AC_BaseAI::StartDamageOverTime(float DamageAmount, float DamageTick, float Time)
{
	// Bind delegate
	DamageOverTimeDelegate.BindUFunction(this, FName("ApplyDamageToAI"), DamageAmount);

	//Calling ApplyDamageToAI with looping
	GetWorld()->GetTimerManager().SetTimer(DamageOverTimeHandle, DamageOverTimeDelegate, DamageTick, true);

	// Will stop looping when this timer is called
	FTimerHandle StopDamageHandle;
	GetWorldTimerManager().SetTimer(StopDamageHandle, this, &AC_BaseAI::EndDamageOverTime, Time, false);
}

void AC_BaseAI::ApplyDamageToAI(float DamageAmount)
{
	// Applies damage
	UGameplayStatics::ApplyDamage(this, DamageAmount, UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerCharacter, NULL);
	CheckForAIDeath();
}

void AC_BaseAI::EndDamageOverTime()
{
	// Stops the damage over time
	GetWorld()->GetTimerManager().ClearTimer(DamageOverTimeHandle);
}

void AC_BaseAI::DestroyAIItems_Implementation()
{

}

void AC_BaseAI::SpawnBurningEffects()
{
	if(!bHasSpawnedFireEffects)
	{
		bHasSpawnedFireEffects = true;

		FireParticleSystemComponentShoulder = UGameplayStatics::SpawnEmitterAttached(FireParticleEffect, GetMesh(), FName("FireHandSocket"));
		FireParticleSystemComponentChest = UGameplayStatics::SpawnEmitterAttached(FireParticleEffect, GetMesh(), FName("FireChestSocket"));
		FireParticleSystemComponentLeg = UGameplayStatics::SpawnEmitterAttached(FireParticleEffect, GetMesh(), FName("FireLegSocket"));

		FireParticleSystemComponentArray.Emplace(FireParticleSystemComponentShoulder);
		FireParticleSystemComponentArray.Emplace(FireParticleSystemComponentChest);
		FireParticleSystemComponentArray.Emplace(FireParticleSystemComponentLeg);
	}
}

// Call when AI enter water volume
void AC_BaseAI::DespawnBurningEffects()
{
	for(auto i : FireParticleSystemComponentArray)
	{
		if(i)
		{
			i->DestroyComponent();
		}
	}

	FireParticleSystemComponentArray.Empty();

	bHasSpawnedFireEffects = false;
}

// Allows ability 2 to work
void AC_BaseAI::MagicStateCollision()
{
	if(BoxComp)
	{
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECR_Overlap);
		//UE_LOG(LogTemp, Log, TEXT("MAGIC"));
	}
}

// Allows crossbow bolts to work
void AC_BaseAI::RangedStateCollision()
{
	if (BoxComp)
	{
		BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECR_Ignore);
		//UE_LOG(LogTemp, Log, TEXT("Rnaged"));
	}
}

void AC_BaseAI::PlayBoltHitMontage()
{
	if(!bHasDied)
	{
		PlayAnimMontage(BoltHitMontage, 1.0f);
		PlayHitGrunt();
	}
}

void AC_BaseAI::UpdateCapsuleForAnimations()
{
	MeshLocation = GetMesh()->GetSocketLocation(HipsSocket) + FVector(0.0f, 0.0f, 20.0f);
	GetCapsuleComponent()->SetWorldLocation(MeshLocation);
	//FVector MeshLoc = GetMesh()->GetComponentLocation();


	//GetCapsuleComponent()->SetWorldLocation(MeshLoc);
}