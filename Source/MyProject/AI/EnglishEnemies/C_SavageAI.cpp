
#include "C_SavageAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AC_SavageAI::AC_SavageAI()
{
	JumpStartTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("JumpStartTimeline"));
	// Here is where we bind our delegates to our functions via function names
	JumpStartInterpFunction.BindUFunction(this, FName("JumpStartTimelineFloatReturn"));
	JumpStartTimelineFinished.BindUFunction(this, FName("OnJumpStartTimelineFinished"));
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
}

void AC_SavageAI::ChangeAIColour()
{
	Super::ChangeAIColour();

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 0);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 1);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 6);
}

// start of the sepcial attack
void AC_SavageAI::BecomeEnraged()
{
	GetMovementComponent()->StopMovementImmediately();
	GetMovementComponent()->StopActiveMovement();

	PlayAnimMontage(EnragedMontage, 1.0f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnragedSound, GetActorLocation());
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
	// spawn at player location then play landed anim with aoe damage
}

void AC_SavageAI::JumpStart()
{
	JumpStartTimeline->PlayFromStart();
}