// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_QuestNPC.generated.h"

UCLASS()
class MYPROJECT_API AC_QuestNPC : public AC_BaseAI, public IC_InteractInterface
{
	GENERATED_BODY()

public:
	AC_QuestNPC();

	virtual void BeginPlay() override;

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

	UFUNCTION()
	void StopInteract(int a);

	//The actor that will give the viewpoint of the camera 
	UPROPERTY(EditInstanceOnly, Category = "NPC")
	AActor* CameraViewPoint;

	FTimerHandle PlayerMeshVisibilityHandle;

	void MakePlayerMeshVisible();

	TArray<AActor*> AttachedActorsArray;

	// A referenec to the quest that this actor should use. The current quest of the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	class AC_BaseQuest* QuestREF;

	FTimerHandle CameraHandle;

	void EnableUIInput();

	void InteractFunctionality();

	UPROPERTY(EditInstanceOnly, Category = "NPC")
	bool bIsQuestGiver;

	void TalkAIFunctionality();

	// If this is a interact NPC (Not quest giver), this will be the text that this AI will say.
	UPROPERTY(EditAnywhere, Category = "NPC")
	TArray<FText> SpeechArray;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "NPC")
	void DestroyAvailableQuestWidget();
};
