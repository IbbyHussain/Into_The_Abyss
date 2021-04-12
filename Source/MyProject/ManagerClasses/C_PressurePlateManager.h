// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/ManagerClasses/C_BaseManagerClass.h"
#include "C_PressurePlateManager.generated.h"

class AC_PressurePlate;
class AC_SpikeDoor;
class AC_TheLabLevel_ManagerClass;

UCLASS()
class MYPROJECT_API AC_PressurePlateManager : public AC_BaseManagerClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PressurePlateManager();

protected:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// The pressure plates
	UPROPERTY(EditInstanceOnly, Category = "Actor to choose")
	AC_PressurePlate* PressurePlate1;
	UPROPERTY(EditInstanceOnly, Category = "Actor to choose")
	AC_PressurePlate* PressurePlate2;
	UPROPERTY(EditInstanceOnly, Category = "Actor to choose")
	AC_PressurePlate* PressurePlate3;

	// An array of all the doors that this class will open(Populated in editor)
	UPROPERTY(EditInstanceOnly)
	TArray<AC_SpikeDoor*> DoorArray;

	// The actor the camera view will come from
	UPROPERTY(EditInstanceOnly, Category = "Actor to choose")
	AActor* CameraViewActor;

	// The number of pressure plates needed to be activated for this class.
	UPROPERTY(EditInstanceOnly, Category = "Number of actors")
	bool b1PressurePlate;
	
	// The number of pressure plates needed to be activated for this class.
	UPROPERTY(EditInstanceOnly, Category = "Number of actors")
	bool b2PressurePlates;
	
	// The number of pressure plates needed to be activated for this class.
	UPROPERTY(EditInstanceOnly, Category = "Number of actors")
	bool b3PressurePlates;

	// The quest that needs this puzzle to complete an objective
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Actor to choose")
	class AC_BaseQuest* Quest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundBase* PuzzleCompleteSound;

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
	class AC_PlayerCharacter* PlayerCharacterRef;

	//Reference to the Player Controller
	class APlayerController* PlayerController;

	UFUNCTION()
	void PuzzleComplete();

};
