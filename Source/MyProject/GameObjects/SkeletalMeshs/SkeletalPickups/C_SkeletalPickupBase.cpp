// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SkeletalPickupBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

AC_SkeletalPickupBase::AC_SkeletalPickupBase()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(MeshComp);

	bDespawn = true;
}

void AC_SkeletalPickupBase::OnInteract(float& Stat, float Amount)
{
	if(bDespawn)
	{
		// clears and restarts timer so that only one fade in and fade out animation are played.
		if(PlayerHUD)
		{
			PlayerHUD->ClearPickupTimer(0.25f);
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation(), 1.0f);

		Stat += Amount;

		DisplayInteractImage();

		DestroyThis();

		bDespawn = false;
	}
}

void AC_SkeletalPickupBase::OnInteractBasic()
{
	if (bDespawn)
	{
		// clears and restarts timer so that only one fade in and fade out animation are played.
		if (PlayerHUD)
		{
			PlayerHUD->ClearPickupTimer(0.25f);
		}

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation(), 1.0f);

		DestroyThis();

		bDespawn = false;
	}
}

void AC_SkeletalPickupBase::DisplayInteractImage()
{
	if(PlayerHUD)
	{
		PlayerHUD->CreatePickupWidget(0.25f);
	}
}

void AC_SkeletalPickupBase::DestroyThis()
{
	Destroy();
}

void AC_SkeletalPickupBase::BeginPlay()
{
	Super::BeginPlay();

	// Gets the referneces for player and player HUD. Used for child classes 
	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
}