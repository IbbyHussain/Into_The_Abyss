// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MoveableObject.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/AudioComponent.h"

AC_MoveableObject::AC_MoveableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = MeshComp;
	MeshComp->SetLinearDamping(5.0f);

	YBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Y Box"));
	XBox = CreateDefaultSubobject<UBoxComponent>(TEXT("X Box"));

	//Physics constraint settings
	PhysicsComp = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Comp"));
	PhysicsComp->ComponentName1.ComponentName = FName("Static Mesh Component");

	PhysicsComp->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PhysicsComp->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PhysicsComp->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	PhysicsComp->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	PhysicsComp->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	PhysicsComp->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45.0f);

	//Collision Events
	YBox->OnComponentBeginOverlap.AddDynamic(this, &AC_MoveableObject::OnOverlapYBoxBegin);
	YBox->OnComponentEndOverlap.AddDynamic(this, &AC_MoveableObject::OnOverlapYBoxEnd);

	XBox->OnComponentBeginOverlap.AddDynamic(this, &AC_MoveableObject::OnOverlapXBoxBegin);
	XBox->OnComponentEndOverlap.AddDynamic(this, &AC_MoveableObject::OnOverlapXBoxEnd);
}

void AC_MoveableObject::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	MovingSoundComponent = UGameplayStatics::SpawnSoundAttached(MovingSound, MeshComp);
	MovingSoundComponent->SetVolumeMultiplier(0.0f);
}

void AC_MoveableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (XBox->IsOverlappingActor(Player) || YBox->IsOverlappingActor(Player))
	{
		Player->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		Player->IsSprinting = false;
		Player->bSprintKeyDown = false;
	}
}

void AC_MoveableObject::OnOverlapYBoxBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == Player)
	{
		MeshComp->SetSimulatePhysics(true);
		Player->MovementState = EMovementState::PUSHING;
		Player->UpdateMovement();
	}
}

void AC_MoveableObject::OnOverlapYBoxEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player)
	{
		MeshComp->SetSimulatePhysics(false);
		Player->MovementState = EMovementState::STANDING;
		Player->UpdateMovement();
	}
}

void AC_MoveableObject::OnOverlapXBoxBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player)
	{
		MeshComp->SetSimulatePhysics(true);
		Player->MovementState = EMovementState::PUSHING;
		Player->UpdateMovement();
	}
}

void AC_MoveableObject::OnOverlapXBoxEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player)
	{
		MeshComp->SetSimulatePhysics(false);
		Player->MovementState = EMovementState::STANDING;
		Player->UpdateMovement();
	}
}

float AC_MoveableObject::CalculateVelocity(float Velocity)
{
	Velocity = MeshComp->GetComponentVelocity().Size();
	return Velocity;
}

void AC_MoveableObject::EnablePhysicsConstraint()
{
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetLinearDamping(5.0f);

	PhysicsComp->ComponentName1.ComponentName = FName("Static Mesh Component");
	PhysicsComp->SetConstrainedComponents(MeshComp, FName("None"), NULL, FName("None"));

	PhysicsComp->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PhysicsComp->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	PhysicsComp->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.0f);

	PhysicsComp->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	PhysicsComp->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	PhysicsComp->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45.0f);
}