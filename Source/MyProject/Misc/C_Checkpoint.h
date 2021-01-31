// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/C_StaticMeshActor.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_Checkpoint.generated.h"

UCLASS()
class MYPROJECT_API AC_Checkpoint : public AC_StaticMeshActor, public IC_InteractInterface
{
	GENERATED_BODY()

public:

	AC_Checkpoint();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "CheckPoint")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category = "CheckPoint")
	class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "CheckPoint")
	USoundBase* BonfireSound;

	// INTERACT

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();


	// Implementation of the interact function
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisplayKeyHint();

	// Implementation of the DisplayKeyHint function
	virtual void DisplayKeyHint_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveKeyHint();

	// Implementation of the RemoveKeyHint function
	virtual void RemoveKeyHint_Implementation() override;

	//REFERENCES

	//Reference to the player character
	class AC_PlayerCharacter* PlayerCharacter;

	//Reference to the HUD
	class AC_PlayerHUD2* HUD;

	// ATTRIBUTES

	bool bOverlappingCheckPoint;

	bool bShowEKeyHintCheckPoint;

	bool bCanInteract;

	bool OverlappingBoxCollision();
	
};
