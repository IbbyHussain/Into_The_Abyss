// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/ManagerClasses/C_BaseManagerClass.h"
#include "C_RotatingPuzzleManager.generated.h"

class AC_RotatingPuzzleActor;
class AC_TheLabLevel_ManagerClass;

UCLASS()
class MYPROJECT_API AC_RotatingPuzzleManager : public AC_BaseManagerClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_RotatingPuzzleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Actor to choose")
	AC_RotatingPuzzleActor* RotatingPuzzle1;

	UPROPERTY(EditAnywhere, Category = "Actor to choose")
	AC_RotatingPuzzleActor* RotatingPuzzle2;

	UPROPERTY(EditAnywhere, Category = "Actor to choose")
	AC_RotatingPuzzleActor* RotatingPuzzle3;

	// The spike door 
	UPROPERTY(EditInstanceOnly, Category = "Actor to choose")
	class AC_SpikeDoor* SpikeDoor;

	// The actor the camera view will come from
	UPROPERTY(EditInstanceOnly, Category = "Actor to choose")
	AActor* CameraViewActor;

	// The number of pressure plates needed to be activated for this class.
	UPROPERTY(EditInstanceOnly, Category = "Number of actors")
	bool b1RotatingPuzzle;

	// The number of pressure plates needed to be activated for this class.
	UPROPERTY(EditInstanceOnly, Category = "Number of actors")
	bool b2RotatingPuzzles;

	// The number of pressure plates needed to be activated for this class.
	UPROPERTY(EditInstanceOnly, Category = "Number of actors")
	bool b3RotatingPuzzles;

	// The quest that needs this puzzle to complete an objective
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Actor to choose")
	class AC_BaseQuest* Quest;

private:	
	//Camera Pan
	void ChangeCameraView();

	void ResetCameraView();

	void ResetPlayerMovement();

	void PlaySpikeDoorAnimation();

	FTimerHandle ResetCameraViewHandle;

	FTimerHandle CameraViewHandle;

	// A do once variable
	bool bDoOnce;

	//Reference to the Player Character
	class AC_PlayerCharacter* PlayerCharacter;

	//Reference to the Player Controller
	class APlayerController* PlayerController;

	//Reference to the HUD
	class AC_PlayerHUD2* HUD;

	UFUNCTION()
	void PuzzleComplete();


};
