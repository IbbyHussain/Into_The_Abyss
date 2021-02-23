// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ExitArea.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_UW_EKeyHint.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
AC_ExitArea::AC_ExitArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComp;
	BoxComp->SetRelativeScale3D(FVector(2.5f));
	BoxComp->SetHiddenInGame(false);

	bCanExit = true;
}

// Called when the game starts or when spawned
void AC_ExitArea::BeginPlay()
{
	Super::BeginPlay();	

	//Ref to the HUD Class
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	//Ref to the player 
	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

bool AC_ExitArea::OverlappingBoxCollision()
{
	// Checks if the Player is overlapping with the Box collision
	if (BoxComp->IsOverlappingActor(PlayerCharacter))
	{
		bOverlappingExitArea = true;
		return bOverlappingExitArea;
	}

	else
	{
		bOverlappingExitArea = false;
		return bOverlappingExitArea;
	}
}

void AC_ExitArea::ExitAreaFixMovement()
{
	HUD->InstantlyInVisible();
	PlayerCharacter->SetActorLocation(NewLocation);
	PlayerCharacter->ExitAreaFixMovement();
	ResetExitArea();
}

void AC_ExitArea::ResetExitArea()
{
	bCanExit = true;
}

void AC_ExitArea::Interact_Implementation()
{
	if (OverlappingBoxCollision() && bCanExit)
	{
		bCanExit = false;

		HUD->PlayExitAreaAnimationHUD();
		HUD->MakeEKeyHintInVisible();

		GetWorldTimerManager().SetTimer(ResetExitAreaHandle, this, &AC_ExitArea::ExitAreaFixMovement, 2.0f, false);

		PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
		PlayerCharacter->GetCharacterMovement()->DisableMovement();

	}
}

void AC_ExitArea::DisplayKeyHint_Implementation()
{
	if (HUD)
	{
		HUD->SetEKeyHintText("Climb");
		HUD->MakeEKeyHintVisible();
	}
}

void AC_ExitArea::RemoveKeyHint_Implementation()
{
	if (HUD)
	{
		HUD->MakeEKeyHintInVisible();
	}
}
