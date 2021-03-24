// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "Components/TimelineComponent.h"
#include "C_RotatingPuzzleActor.generated.h"

UENUM()
enum class EPuzzleFacingDirection : uint8
{
	BEAR, //FORWARDS
	SNAKE, // BACKWARDS
	SCORPION, // RIGHT
	WOLF // LEFT
};

class UBoxComponent;
class UAnimationAsset;

UCLASS()
class MYPROJECT_API AC_RotatingPuzzleActor : public AC_StaticMeshActor, public IC_InteractInterface
{
	GENERATED_BODY()

public:
	bool bRightDirection;

protected:

	AC_RotatingPuzzleActor();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	UBoxComponent* BoxComp;

	//UPROPERTY(EditAnywhere, Category = "Puzzle")
	//UBoxComponent* Collision;

	// The Direction this actor needs to face in order for the puzzle to be completed
	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	EPuzzleFacingDirection CorrectDirection;

	//Sound Played when the actor is rotated
	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	USoundBase* PuzzleSound;

	//Checks if the Player is overlapping the Puzzles collision
	bool OverlappingPuzzleBoxCollision();

	bool bOverlappingPuzzle;

	//Resets the bool bCanRotateActor so that the puzzle actor can be rotated again
	void ResetbCanRotateActor();

	// The curve that controls the rotation of the actor
	UPROPERTY(EditDefaultsOnly, Category = "Puzzle")
	UCurveFloat* FRotationCurve;

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline1FloatReturn(float Value);

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline2FloatReturn(float Value);

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline3FloatReturn(float Value);

	// The function to be binded to interp (update)
	UFUNCTION()
	void Timeline4FloatReturn(float Value);

	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;

	// DisplayKeyhint function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisplayKeyHint();

	// Implementation of the DisplayKeyHint function
	virtual void DisplayKeyHint_Implementation() override;

	// RemoveKeyhint function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveKeyHint();

	// Implementation of the RemoveKeyHint function
	virtual void RemoveKeyHint_Implementation() override;

private:

	//Ref to the Player Character
	class AC_PlayerCharacter* PlayerCharacter;

	//Ref to the HUD
	class AC_PlayerHUD2* HUD;

	bool bCanRotateActor;

	FTimerHandle ResetPuzzleHandle;

	//Used to keep track of the actors facing direction
	int32 PuzzleCounter;

	//Timeline1
	UPROPERTY()
	UTimelineComponent* Timeline1;
	FOnTimelineFloat Timeline1InterpFunction{};

	//Timeline 2
	UPROPERTY()
	UTimelineComponent* Timeline2;
	FOnTimelineFloat Timeline2InterpFunction{};

	//Timeline 3
	UPROPERTY()
	UTimelineComponent* Timeline3;
	FOnTimelineFloat Timeline3InterpFunction{};

	//Timeline 4
	UPROPERTY()
	UTimelineComponent* Timeline4;
	FOnTimelineFloat Timeline4InterpFunction{};

	//Timer Handles for each rotation
	FTimerHandle RotateHandle1;
	FTimerHandle RotateHandle2;
	FTimerHandle RotateHandle3;
	FTimerHandle RotateHandle4;

	// These are the value of each timeline and are added to the next timelines value to enure it rotates the right way.
	// and starts from the last timelines end position
	float Timeline1Value;
	float Timeline2Value;
	float Timeline3Value;

	//Stops the previous timeline from playing
	bool bCanPlayTimeline1;
	bool bCanPlayTimeline2;
	bool bCanPlayTimeline3;
	bool bCanPlayTimeline4;

	// Roll, Yaw and Pitch
	float r;
	float y;
	float z;

	//Checks the current direction the actor is facing
	void CheckFacingDirection();

	// Decides which Timeline should be played
	void ChooseAnimToPlay();


};


