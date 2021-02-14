// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Crossbowbolt.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/C_BaseAI.h"
#include "Kismet/KismetSystemLibrary.h" // for the debug line
#include "CollisionQueryParams.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Particles/ParticleSystemComponent.h"
#include "MyProject/C_PlayerCharacter.h"

// For collision 
#include "MyProject\MyProject.h"
#include "Engine/CollisionProfile.h"

#include "MyProject/UI/C_PlayerHUD2.h"

AC_Crossbowbolt::AC_Crossbowbolt()
{
	bIsPlayerBolt = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	CollisionComponent->bReturnMaterialOnMove = true;

	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	CollisionComponent->SetBoxExtent(FVector(14.0f, 5.0f, 5.0f));

	// Collision Settings for CollisionComponent
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);


	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	CollisionComponent->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(COLLISION_ABILITY1DETECTION, ECollisionResponse::ECR_Overlap);

	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(COLLISION_AIHEALTHDETECTION, ECollisionResponse::ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(COLLISION_CROSSBOWBOLTDETECTION, ECollisionResponse::ECR_Ignore);

	// Mesh comp settings

	MeshComp->SetupAttachment(RootComponent);

	MeshComp->SetRelativeLocation(FVector(6.0f, 0.0f, 0.0f));
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); //.Quaternion()

	//Collision settings for mesh

	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	MeshComp->SetCollisionResponseToChannel(COLLISION_ABILITY1DETECTION, ECollisionResponse::ECR_Overlap);
	MeshComp->SetCollisionResponseToChannel(COLLISION_AIHEALTHDETECTION, ECollisionResponse::ECR_Ignore);
	MeshComp->SetCollisionResponseToChannel(COLLISION_CROSSBOWBOLTDETECTION, ECollisionResponse::ECR_Ignore);

	// Projectile Settings

	DefaultGravity = 0.0f;
	DefaultGravity = 2000.0f;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = DefaultGravity;
	ProjectileMovementComponent->MaxSpeed = DefaultGravity;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = DefaultGravity;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_Crossbowbolt::OnOverlapBegin);

	BoltDamage = 0.1f;

	bHasOverlapped = false;

	NumberOfBolts = 99;
}

void AC_Crossbowbolt::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Crossbowbolt::SetGravity(float Gravity)
{
	ProjectileMovementComponent->ProjectileGravityScale = Gravity;
}

void AC_Crossbowbolt::SetVelocity(float Velocity)
{
	ProjectileMovementComponent->InitialSpeed = Velocity;
	ProjectileMovementComponent->MaxSpeed = Velocity;
}

void AC_Crossbowbolt::SpawnHitEffect()
{
	UE_LOG(LogTemp, Log, TEXT("Spawn hit effect"));
}

void AC_Crossbowbolt::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AC_Crossbowbolt::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensures will only collide once
	if(bHasOverlapped == false)
	{
		// If the bolt is fired from a player
		if(bIsPlayerBolt)
		{
			AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(OtherActor);

			if (OtherActor != Character && OtherActor != this && OtherActor)
			{
				SpawnHitEffect();

				AC_BaseAI* AI = Cast<AC_BaseAI>(OtherActor);

				if (OtherActor == AI && OtherComp == AI->GetMesh() && OtherComp != AI->BoxComp)
				{
					UE_LOG(LogTemp, Error, TEXT("BOLT HIT AI"));

					bHasOverlapped = true;

					StopBolt();

					UGameplayStatics::ApplyDamage(AI, BoltDamage, UGameplayStatics::GetPlayerController(this, 0), this, NULL);

					AI->CheckForAIDeath();

					AttachToComponent(AI->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, SweepResult.BoneName);

					//UE_LOG(LogTemp, Log, TEXT("Bone name is: %s"), *SweepResult.BoneName.ToString());

					if (bShouldStaggerAI)
					{
						AI->PlayBoltHitMontage();
					}
				}

				// If we dont hit this and player and an AI then the bolt will stick to a wall 
				else if (OtherActor != this && OtherActor != Character && AI == nullptr)
				{
					StopBolt();

					//UE_LOG(LogTemp, Log, TEXT("OBJECT"));
				}
			}
		}

		// If the bolt is fired from an AI
		else
		{
			AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(OtherActor);

			AC_BaseAI* AI = Cast<AC_BaseAI>(OtherActor);

			if (OtherActor != AI && OtherActor != this && OtherActor)
			{
				SpawnHitEffect();

				if (OtherActor == Character && OtherComp == Character->GetMesh())
				{
					UE_LOG(LogTemp, Error, TEXT("BOLT HIT Player"));

					bHasOverlapped = true;

					//StopBolt();

				}

				// If we dont hit this and player and an AI then the bolt will stick to a wall 
				else if (OtherActor != this && OtherActor != Character && AI == nullptr)
				{
					StopBolt();

					//UE_LOG(LogTemp, Log, TEXT("OBJECT"));
				}
			}
		}
	}

}

void AC_Crossbowbolt::StopBolt()
{
	//SetLifeSpan(5.0f);

	// Stops the projectile 
	ProjectileMovementComponent->SetComponentTickEnabled(false);

	// Removes collision from projectile 
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	//Play particle Effect
	if(BoltHitParticle)
	{
		BoltHitParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BoltHitParticle, GetActorTransform());
	}

	// Play Sound
	if(BoltHitSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BoltHitSound, GetActorLocation());
	}
}

bool AC_Crossbowbolt::CanFire()
{
	if(NumberOfBolts <= 0)
	{
		return false;
	}

	return true;
}


/*// Gets a ptr to the AI bone name in skeletal mesh
		FBodyInstance* BodyInstance = AI->GetMesh()->GetBodyInstance(FName("Head"));

		// Get the physical material of that bone
		UPhysicalMaterial* AIHeadMat = BodyInstance->GetSimplePhysicalMaterial();

		UE_LOG(LogTemp, Log, TEXT("Phys material of head is: %s"), *AIHeadMat->GetName());*/