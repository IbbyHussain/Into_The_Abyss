// Fill out your copyright notice in the Description page of Project Settings.


#include "C_IceSpike.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/AI/Creatures/C_RollerAI.h"

AC_IceSpike::AC_IceSpike()
{
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	//BoxComp->SetupAttachment(Root);
	RootComponent = BoxComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(BoxComp);

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Comp"));
	TrailEffect->SetupAttachment(MeshComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Comp"));

	MovementComp->InitialSpeed = 2000.0f;
	MovementComp->MaxSpeed = 2000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->bRotationFollowsVelocity = true;

	MovementComp->bAutoActivate = false;
}

void AC_IceSpike::BeginPlay()
{
	Super::BeginPlay();

	MovementComp->OnProjectileStop.AddDynamic(this, &AC_IceSpike::OnHit);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SummonSound, GetActorLocation());
}

void AC_IceSpike::Fire()
{
	MovementComp->Activate();
}

void AC_IceSpike::StopFire()
{

}

void AC_IceSpike::OnHit(const FHitResult& Hit)
{
	//Ability2 = Cast<AC_Ability2>(OtherActor);
	BaseAI = Cast<AC_BaseAI>(Hit.GetActor());
	AC_RollerAI* RollerAI = Cast<AC_RollerAI>(Hit.GetActor());

	if(Hit.GetActor() == BaseAI)
	{
		//UE_LOG(LogTemp, Log, TEXT("Hit BaseAI / Ability 4 death"));
		BaseAI->BecomeFrozen();
		UGameplayStatics::ApplyDamage(Hit.GetActor(), 0.1f, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
		BaseAI->CheckForAIDeath();

		//UE_LOG(LogTemp, Log, TEXT("Ability 2 Death"));
		//BaseAI->TypeOfDeath = ETypeOfDeath::ABILITY4DEATH;
	}

	if (Hit.GetActor() == RollerAI)
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), 1.0f, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroyedSound, Hit.Location);

	SpawnDestroyedEffect();
}

void AC_IceSpike::SpawnDestroyedEffect()
{
	FTransform DestroyEffectTransform;
	DestroyEffectTransform.SetLocation(GetActorLocation());
	DestroyEffectTransform.SetRotation(GetActorRotation().Quaternion());
	DestroyEffectComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, DestroyEffectTransform);
	GetWorldTimerManager().SetTimer(ExplosionEffectHandle, this, &AC_IceSpike::DestroyActor, 0.5f, false);

}

void AC_IceSpike::DestroyActor()
{
	Destroy();
}


