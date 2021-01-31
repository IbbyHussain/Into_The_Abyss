// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Checkpoint.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

AC_Checkpoint::AC_Checkpoint()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComp->SetupAttachment(Root);

	MeshComp->SetupAttachment(Root);

	bOverlappingCheckPoint = false;

    bShowEKeyHintCheckPoint = true;

	bCanInteract = true;
}

void AC_Checkpoint::BeginPlay()
{
	Super::BeginPlay();

	// References 
	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

bool AC_Checkpoint::OverlappingBoxCollision()
{
	if (BoxComp->IsOverlappingActor(PlayerCharacter))
	{
		bOverlappingCheckPoint = true;
		return bOverlappingCheckPoint;
	}

	else
	{
		bOverlappingCheckPoint = false;
		return bOverlappingCheckPoint;
	}
}

// INTERACT

void AC_Checkpoint::Interact_Implementation()
{
	if (OverlappingBoxCollision() && bCanInteract)
	{
		RemoveKeyHint_Implementation();
		bShowEKeyHintCheckPoint = false;
		bCanInteract = false;

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, GetActorLocation(), FRotator::ZeroRotator);

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BonfireSound, GetActorLocation(), 1.0f);

		if(PlayerCharacter)
		{
			PlayerCharacter->SavePlayerLocation();
		}
		// Save player loc here 
	}
}

void AC_Checkpoint::DisplayKeyHint_Implementation()
{
	if (bShowEKeyHintCheckPoint)
	{
		if (HUD)
		{
			HUD->SetEKeyHintText("activate save point.");
			HUD->MakeEKeyHintVisible();
		}
	}
}

void AC_Checkpoint::RemoveKeyHint_Implementation()
{
	if (bShowEKeyHintCheckPoint)
	{
		if (HUD)
		{
			HUD->MakeEKeyHintInVisible();
		}
	}
}

