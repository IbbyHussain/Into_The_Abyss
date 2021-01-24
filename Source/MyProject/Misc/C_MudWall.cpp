// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MudWall.h"
#include "MyProject/Components/C_HealthComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleComponent.h"
#include "Particles/ParticleSystemComponent.h"

AC_MudWall::AC_MudWall()
{
	HealthComp = CreateDefaultSubobject<UC_HealthComponent>(TEXT("HealthComp"));

	DestructibleMeshComp = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible mesh Comp"));
	DestructibleMeshComp->SetupAttachment(MeshComp);
	DestructibleMeshComp->SetVisibility(false);

	WallTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("WallTimeline"));
	// Here is where we bind our delegates to our functions via function names
	WallInterpFunction.BindUFunction(this, FName("WallTimelineFloatReturn"));
}

void AC_MudWall::BeginPlay()
{
	Super::BeginPlay();

	// Gives us access to this delegate 
	HealthComp->OnHealthChanged.AddDynamic(this, &AC_MudWall::UpdateHealth);

	if (FWallCurve)
	{
		// Now we set the functions and some values.
		WallTimeline->AddInterpFloat(FWallCurve, WallInterpFunction, FName("Alpha"));
		WallTimeline->SetLooping(false);
	}

	float WallHeightX = MeshComp->GetRelativeLocation().X;
	float WallHeightY = MeshComp->GetRelativeLocation().Y;
	float WallHeightZ = MeshComp->GetRelativeLocation().Z;

	StartLocation = GetActorLocation();
	EndLocation = FVector(WallHeightX, WallHeightY, (WallHeightZ + 5500.0f));

}

void AC_MudWall::PlayWallAnim()
{
	WallTimeline->PlayFromStart();

	PlaySummonEffect();
}

void AC_MudWall::WallTimelineFloatReturn(float Value)
{
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value));
}

void AC_MudWall::UpdateHealth(UC_HealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Health <= 0.75f)
	{
		UE_LOG(LogTemp, Log, TEXT("0.75 Health"));
		MeshComp->SetStaticMesh(State75);
	}

	if (Health <= 0.5f)
	{
		UE_LOG(LogTemp, Log, TEXT("0.50 Health"));
		MeshComp->SetStaticMesh(State50);
	}

	if (Health <= 0.25f)
	{
		UE_LOG(LogTemp, Log, TEXT("0.25 Health"));
		MeshComp->SetStaticMesh(State25);
	}


	if (Health <= 0.0f)
	{

		//Mud wall death
		MeshComp->SetVisibility(false);
		MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		DestructibleMeshComp->SetVisibility(true);

		// Causes mud wall to fracture into DM
		DestructibleMeshComp->ApplyRadiusDamage(2500.0f, GetActorLocation(), 2500.0f, 2500.0f, true);

		// put in do once
		if(!bHasDied)
		{
			bHasDied = true;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestroyedSound, GetActorLocation(), GetActorRotation(), 1.0f);

			DespawnSummonEffect();

			PlayDeSummonEffect();
		}

		FTimerHandle DestroyHandle;
		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AC_MudWall::DestroyWall, 5.0f, false);
		
	}

	else 
	{
		//UE_LOG(LogTemp, Log, TEXT("Alive"));
	}
}

void AC_MudWall::PlaySummonedSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SummonedSound, GetActorLocation(), GetActorRotation(), 1.0f);
}

void AC_MudWall::PlaySummonEffect()
{
	FTransform SummonEffectTransform;
	SummonEffectTransform.SetLocation(GetActorLocation());
	SummonEffectTransform.SetRotation(GetActorRotation().Quaternion());
	SummonEffectTransform.SetScale3D(FVector(3.0f));
	SummonEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SummonEffect, SummonEffectTransform);
}

void AC_MudWall::PlayDeSummonEffect()
{
	FTransform DeSummonEffectTransform;
	DeSummonEffectTransform.SetLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z * 2.0f));
	DeSummonEffectTransform.SetRotation(GetActorRotation().Quaternion());
	DeSummonEffectTransform.SetScale3D(FVector(3.0f));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeSummonEffect, DeSummonEffectTransform);
}

void AC_MudWall::DespawnSummonEffect()
{
	if(SummonEffectComponent)
	{
		SummonEffectComponent->DestroyComponent();
	}
}

void AC_MudWall::DestroyWall()
{
	Destroy();
}
