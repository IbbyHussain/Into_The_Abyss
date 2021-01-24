// Fill out your copyright notice in the Description page of Project Settings.


#include "C_RotatingPuzzleActor.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "TimerManager.h"

AC_RotatingPuzzleActor::AC_RotatingPuzzleActor()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	//Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	bOverlappingPuzzle= false;

	bCanRotateActor = true;

	PuzzleCounter = 0;

	//TIMELINES
	Timeline1 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline1"));
	Timeline1InterpFunction.BindUFunction(this, FName("Timeline1FloatReturn"));

	Timeline2 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline2"));
	Timeline2InterpFunction.BindUFunction(this, FName("Timeline2FloatReturn"));

	Timeline3 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline3"));
	Timeline3InterpFunction.BindUFunction(this, FName("Timeline3FloatReturn"));

	Timeline4 = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline4"));
	Timeline4InterpFunction.BindUFunction(this, FName("Timeline4FloatReturn"));

	Timeline1Value = 0.0f;
	Timeline2Value = 0.0f;
	Timeline3Value = 0.0f;

	bCanPlayTimeline1 = true;
	bCanPlayTimeline2 = true;
	bCanPlayTimeline3 = true;
	bCanPlayTimeline4 = true;

	// Gets the relative rotation, used for the  timelines.
	r = MeshComp->GetRelativeRotation().Roll;
	y = MeshComp->GetRelativeRotation().Pitch;
	z = MeshComp->GetRelativeRotation().Yaw;
}

void AC_RotatingPuzzleActor::BeginPlay()
{
	Super::BeginPlay();

	//Ref to the player 
	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	//Ref to the HUD Class
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	//no longer parents the componenet to the root
	BoxComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	CheckFacingDirection();

	//Settings for the timelines
	if (FRotationCurve)
	{
		Timeline1->AddInterpFloat(FRotationCurve, Timeline1InterpFunction, FName("Alpha"));
		Timeline1->SetLooping(false);

		Timeline2->AddInterpFloat(FRotationCurve, Timeline2InterpFunction, FName("Bravo"));
		Timeline2->SetLooping(false);

		Timeline3->AddInterpFloat(FRotationCurve, Timeline3InterpFunction, FName("charlie"));
		Timeline3->SetLooping(false);

		Timeline4->AddInterpFloat(FRotationCurve, Timeline4InterpFunction, FName("Delta"));
		Timeline4->SetLooping(false);
	}
}

void AC_RotatingPuzzleActor::ResetbCanRotateActor()
{
	bCanRotateActor = true;
	GetWorldTimerManager().ClearTimer(ResetPuzzleHandle);
}

bool AC_RotatingPuzzleActor::OverlappingPuzzleBoxCollision()
{
	// Checks if the Player is overlapping with the Box collision
	if (BoxComp->IsOverlappingActor(PlayerCharacter))
	{
		bOverlappingPuzzle = true;
		return bOverlappingPuzzle;
	}

	else
	{
		bOverlappingPuzzle = false;
		return bOverlappingPuzzle;
	}
}

void AC_RotatingPuzzleActor::Timeline1FloatReturn(float Value)
{
	//Rotates the actor by 90 degress
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value, 0.0f));
	Timeline1Value = Value;
}

void AC_RotatingPuzzleActor::Timeline2FloatReturn(float Value)
{
	//Rotates the actor by 90 degress (180 degress total)
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value + Timeline1Value, 0.0f));
	Timeline2Value = Value;
}

void AC_RotatingPuzzleActor::Timeline3FloatReturn(float Value)
{
	//Rotates the actor by 90 degress (270 degress total)
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value + Timeline1Value + Timeline2Value, 0.0f));
	Timeline3Value = Value;
}

void AC_RotatingPuzzleActor::Timeline4FloatReturn(float Value)
{
	//Rotates the actor by 90 degress (360 degress total)
	MeshComp->SetWorldRotation(FRotator(0.0f, y + Value + Timeline1Value + Timeline2Value + Timeline3Value, 0.0f));
}

void AC_RotatingPuzzleActor::CheckFacingDirection()
{
	if (CorrectDirection == EPuzzleFacingDirection::BEAR)
	{
		PuzzleCounter == 0 ? bRightDirection = true: bRightDirection = false;
	}

	else if (CorrectDirection == EPuzzleFacingDirection::SCORPION)
	{
		PuzzleCounter == 1 ? bRightDirection = true : bRightDirection = false;
	}

	else if (CorrectDirection == EPuzzleFacingDirection::SNAKE)
	{
		PuzzleCounter == 2 ? bRightDirection = true : bRightDirection = false;
	}

	else if (CorrectDirection == EPuzzleFacingDirection::WOLF)
	{
		PuzzleCounter == 3 ? bRightDirection = true : bRightDirection = false;
	}
}

void AC_RotatingPuzzleActor::ChooseAnimToPlay()
{
	CheckFacingDirection();

	if(PuzzleCounter == 1 && bCanPlayTimeline1)
	{
		Timeline1->PlayFromStart();
		bCanPlayTimeline1 = false;
		bCanPlayTimeline4 = true;
		GetWorldTimerManager().SetTimer(RotateHandle1, this, &AC_RotatingPuzzleActor::ChooseAnimToPlay, 4.0f, false);
	}

	else if (PuzzleCounter == 2 && bCanPlayTimeline2)
	{
		Timeline2->PlayFromStart();
		GetWorldTimerManager().SetTimer(RotateHandle2, this, &AC_RotatingPuzzleActor::ChooseAnimToPlay, 4.0f, false);
		bCanPlayTimeline2 = false;
		bCanPlayTimeline1 = true;
		GetWorldTimerManager().ClearTimer(RotateHandle1);
	}

	else if (PuzzleCounter == 3 && bCanPlayTimeline3)
	{
		Timeline3->PlayFromStart();
		GetWorldTimerManager().SetTimer(RotateHandle3, this, &AC_RotatingPuzzleActor::ChooseAnimToPlay, 4.0f, false);
		bCanPlayTimeline3 = false;
		bCanPlayTimeline2 = true;
		GetWorldTimerManager().ClearTimer(RotateHandle2);
	}

	else if (PuzzleCounter == 4 && bCanPlayTimeline4)
	{
		Timeline4->PlayFromStart();
		PuzzleCounter = 0;
		GetWorldTimerManager().SetTimer(RotateHandle4, this, &AC_RotatingPuzzleActor::ChooseAnimToPlay, 4.0f, false);
		GetWorldTimerManager().ClearTimer(RotateHandle3);
		bCanPlayTimeline4 = false;
		bCanPlayTimeline3 = true;
	}
}

void AC_RotatingPuzzleActor::Interact_Implementation()
{
	// Will rotate the puzzle actor, only allows the actor to be rotated every 4 seconds.
	if (OverlappingPuzzleBoxCollision() && bCanRotateActor)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PuzzleSound, GetActorLocation());
		bCanRotateActor = false;
		GetWorldTimerManager().SetTimer(ResetPuzzleHandle, this, &AC_RotatingPuzzleActor::ResetbCanRotateActor, 4.0f, false);
		PuzzleCounter++;
		ChooseAnimToPlay();
	}
}

void AC_RotatingPuzzleActor::DisplayKeyHint_Implementation()
{
	if (HUD)
	{
		HUD->SetEKeyHintText("Rotate");
		HUD->MakeEKeyHintVisible();
	}
}

void AC_RotatingPuzzleActor::RemoveKeyHint_Implementation()
{
	if (HUD)
	{
		HUD->MakeEKeyHintInVisible();
	}
}
