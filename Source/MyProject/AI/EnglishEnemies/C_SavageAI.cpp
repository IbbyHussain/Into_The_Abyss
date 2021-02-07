
#include "C_SavageAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "DrawDebugHelpers.h"
#include "MyProject/MyProject.h"

AC_SavageAI::AC_SavageAI()
{
	JumpStartTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("JumpStartTimeline"));
	JumpStartInterpFunction.BindUFunction(this, FName("JumpStartTimelineFloatReturn"));
	JumpStartTimelineFinished.BindUFunction(this, FName("OnJumpStartTimelineFinished"));

	LandTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("LandTimeline"));
	LandInterpFunction.BindUFunction(this, FName("LandTimelineFloatReturn"));
	LandTimelineFinished.BindUFunction(this, FName("OnLandTimelineFinished"));

	bCanSpecialAttackDamagePlayer = true;
}

void AC_SavageAI::BeginPlay()
{
	Super::BeginPlay();

	//Sets the values of the slide timeline
	if (FJumpCurve)
	{
		// Now we set the functions and some values.
		JumpStartTimeline->AddInterpFloat(FJumpCurve, JumpStartInterpFunction, FName("Alpha"));
		JumpStartTimeline->SetTimelineFinishedFunc(JumpStartTimelineFinished);
		JumpStartTimeline->SetLooping(false);
	}

	if (FLandCurve)
	{
		// Now we set the functions and some values.
		LandTimeline->AddInterpFloat(FLandCurve, LandInterpFunction, FName("Bravo"));
		LandTimeline->SetTimelineFinishedFunc(LandTimelineFinished);
		LandTimeline->SetLooping(false);
	}
}

void AC_SavageAI::ChangeAIColour()
{
	Super::ChangeAIColour();

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 0);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 1);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 6);
}

void AC_SavageAI::BecomeEnraged()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	PlayAnimMontage(EnragedMontage, 1.0f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnragedSound, GetActorLocation());

	FTimerHandle JumpHandle;
	GetWorldTimerManager().SetTimer(JumpHandle, this, &AC_SavageAI::PlayJumpStartAnim, 1.5f, false);
}

void AC_SavageAI::PlayJumpStartAnim()
{
	PlayAnimMontage(JumpStartMontage, 1.0f);
}

void AC_SavageAI::JumpStartTimelineFloatReturn(float Value)
{
	float X = GetActorLocation().X;
	float Y = GetActorLocation().Y;
	float Z = GetActorLocation().Z;
	SetActorLocation(FVector(X, Y, (FMath::Lerp(Z, Z + 10.0f, Value))));
}

void AC_SavageAI::OnJumpStartTimelineFinished()
{
	AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Hides weapon and AI mesh
	SetActorHiddenInGame(true);
	Weapon->SetActorHiddenInGame(true);
	SpawnSavageIndicator();

	// Moves the savage AI above the player character
	SetActorLocation(FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, GetActorLocation().Z));

	GetWorldTimerManager().SetTimer(LandHandle, this, &AC_SavageAI::Land, 6.0f, false);
}

void AC_SavageAI::SpawnSavageIndicator()
{
	AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FVector PlayerLocation = Player->GetActorLocation();
	FActorSpawnParameters SpawnParams;
	SavageIndicator = GetWorld()->SpawnActor<AC_StaticMeshActor>(SavageIndicatorClass, FVector(PlayerLocation.X, PlayerLocation.Y, PlayerLocation.Z - 90.0f), FRotator::ZeroRotator, SpawnParams);
}

void AC_SavageAI::JumpStart()
{
	JumpStartTimeline->PlayFromStart();
	PlayAnimMontage(JumpLoopMontage, 1.0f);
}

void AC_SavageAI::Land()
{
	LandTimeline->PlayFromStart();
	SetActorHiddenInGame(false);
	Weapon->SetActorHiddenInGame(false);
	PlayAnimMontage(LandLoopMontage, 1.0f);
}

void AC_SavageAI::LandTimelineFloatReturn(float Value)
{
	float X = GetActorLocation().X;
	float Y = GetActorLocation().Y;
	float Z = GetActorLocation().Z;
	SetActorLocation(FVector(X, Y, (FMath::Lerp(Z, Z - 10.0f, Value))));
}

void AC_SavageAI::OnLandTimelineFinished()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	PlayAnimMontage(LandMontage, 1.0f);

	// Spawns shockwave particle
	FTransform ParticleTransform;
	ParticleTransform.SetScale3D(FVector(1.25f));
	ParticleTransform.SetLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 90.0f));
	ParticleTransform.SetRotation(FRotator(0.0f, 0.0f, 0.0f).Quaternion());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShockWave, ParticleTransform);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LandSound, GetActorLocation());
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	FCollisionQueryParams CollisionParams;
	TArray<FHitResult> OutHits;

	FVector ActorLocation = GetActorLocation();

	// Creates a sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.0f);

	// Debug
	DrawDebugSphere(GetWorld(), ActorLocation, MyColSphere.GetSphereRadius(), 20, FColor::Green, true);

	// A sweep trace that will hit anything within the sphere
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, COLLISION_AIMELEEDETECTION, MyColSphere, CollisionParams);

	if (bHit)
	{
		for (auto& Hit : OutHits)
		{
			AC_PlayerCharacter* PlayerCharacterPTR = Cast<AC_PlayerCharacter>(Hit.Actor);

			UE_LOG(LogTemp, Error, TEXT("HIT Hit: %s"), *Hit.GetActor()->GetName());

			if (Hit.GetActor() == PlayerCharacterPTR && bCanSpecialAttackDamagePlayer)
			{
				bCanSpecialAttackDamagePlayer = false;
				PlayerCharacterPTR->ApplyDamageToPlayer(35.0f);

				// Play Camera shake if caught in damage field
				APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
				PlayerController->ClientPlayCameraShake(ShockWaveCameraShake);
			}
		}
	}

	GetWorldTimerManager().SetTimer(ResetMovementHandle, this, &AC_SavageAI::ResetMovement, 1.5f, false);
}

void AC_SavageAI::ResetMovement()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bCanSpecialAttackDamagePlayer = true;
}
