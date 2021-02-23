// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_ExitArea.generated.h"

class UC_UW_EKeyHint;
class AC_ExitAreaSpawnLocation;


UCLASS()
class MYPROJECT_API AC_ExitArea : public AActor, public IC_InteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ExitArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* BoxComp;

	class AC_PlayerCharacter* PlayerCharacterRef;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	UC_UW_EKeyHint* EKeyHintWidget;

	TSubclassOf<UC_UW_EKeyHint> WidgetClass;

	// INTERACT 

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

	//Ref to the HUD
	class AC_PlayerHUD2* HUD;

	//Ref to the Player Character
	class AC_PlayerCharacter* PlayerCharacter;

	bool OverlappingBoxCollision();

	bool bOverlappingExitArea;

	bool bCanExit;

	FTimerHandle ResetExitAreaHandle;

	void ResetExitArea();

	void ExitAreaFixMovement();

	// The location the player will spawn at after interacting with this exit area actor
	UPROPERTY(EditInstanceOnly, Category = "Exit Area")
	FVector NewLocation;
};
