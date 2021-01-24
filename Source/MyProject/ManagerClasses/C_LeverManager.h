#pragma once
#include "CoreMinimal.h"
#include "MyProject/ManagerClasses/C_BaseManagerClass.h"
#include "C_LeverManager.generated.h"

class AC_BaseAnimLever;
class AC_SpikeDoor;
class AC_TheLabLevel_ManagerClass;

UCLASS()
class MYPROJECT_API AC_LeverManager : public AC_BaseManagerClass
{
	GENERATED_BODY()
	
public:	
	AC_LeverManager();

	UPROPERTY(EditInstanceOnly, Category = "Manager")
	AC_TheLabLevel_ManagerClass* LevelManager;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateboolArray();

	// The array that holds all the levers this class wants to use. (Populated in editor)
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AC_BaseAnimLever*> LeverArray;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<bool> boolArray;

	// An array of all the doors that this class will open (Populated in editor)
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AC_SpikeDoor*> DoorArray;

	// Will check if all the levers in the lever array have been interacted with.
	void CheckLever();

	//The actor that will give the viewpoint of the camera 
	UPROPERTY(EditInstanceOnly, Category = "Lever")
	AActor* CameraViewPoint;

	void ChangeCameraView();

	void ResetCameraView();

	FTimerHandle ResetCameraViewHandle;

	FTimerHandle CameraViewHandle;

	void ResetMovement();

	void PlaySpikeDoorAnimation();

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	class AC_PlayerCharacter* PlayerCharacter;

	class APlayerController* PlayerController;

};
