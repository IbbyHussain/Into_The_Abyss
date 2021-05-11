// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CopperBoltBomblet.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/MyProject.h"

AC_CopperBoltBomblet::AC_CopperBoltBomblet()
{
	// Stops the bomblets coliding with each other at spawn
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECR_Overlap);
}

void AC_CopperBoltBomblet::BeginPlay()
{
	Super::BeginPlay();

	MatInst = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMaterial(0));

	// Will pulse every 0.25 seconds, using pulse material
	GetWorldTimerManager().SetTimer(PulseHandle, this, &AC_CopperBoltBomblet::Pulse, 0.35, true);
}

void AC_CopperBoltBomblet::Pulse()
{
	MatInst->SetScalarParameterValue("LastTimeDamagedTaken", GetWorld()->TimeSeconds);
}

void AC_CopperBoltBomblet::Launch()
{
	//Allows the bomblet to have an arc when it is launched
	float x = MeshComp->GetRightVector().X;
	float y = MeshComp->GetRightVector().Y;
	MeshComp->AddForce(FVector(x * 150000.0f, y * 150000.0f, 1100000.0f));

	// Bomblet explodes after timer
	GetWorldTimerManager().SetTimer(ExplodeHandle, this, &AC_CopperBoltBomblet::Explode, 2.0f, false);
}


void AC_CopperBoltBomblet::Explode()
{
	FCollisionQueryParams CollisionParams;

	TArray<FHitResult> OutHits;

	FVector ActorLocation = GetActorLocation();

	// Creates a sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(75.0f);

	// Debug 
	//DrawDebugSphere(GetWorld(), ActorLocation, MyColSphere.GetSphereRadius(), 20, FColor::Green, true);

	// A sweep trace that will hit anything within the sphere
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, COLLISION_COPPERBOLTDETECTION, MyColSphere, CollisionParams);

	TArray<AC_BaseAI*> AIs;

	if (bHit)
	{
		for (auto& Hit : OutHits)
		{
			AC_BaseAI* AI = Cast<AC_BaseAI>(Hit.Actor);

			UE_LOG(LogTemp, Error, TEXT("Bomblet Hit: %s"), *Hit.GetActor()->GetName());

			if (Hit.GetActor() == AI)
			{
				if(AI->bIsBoss)
				{
					UGameplayStatics::ApplyDamage(AI, 0.1f * AI->BossDamageReduction, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
				}
				else
				{
					UGameplayStatics::ApplyDamage(AI, 0.1f, UGameplayStatics::GetPlayerController(this, 0), this, NULL);
				}
				
				AI->CheckForAIDeath();
			}
		}
	}

	//Play particle Effect
	if (BombletExplodeParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BombletExplodeParticle, GetActorTransform());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BombletExplodeSound, GetActorLocation());
	}

	Destroy();
}
