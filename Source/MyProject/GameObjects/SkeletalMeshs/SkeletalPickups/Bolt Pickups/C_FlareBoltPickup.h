// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SkeletalPickupBase.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_FlareBoltPickup.generated.h"

UCLASS()
class MYPROJECT_API AC_FlareBoltPickup : public AC_SkeletalPickupBase, public IC_InteractInterface
{
	GENERATED_BODY()

public:
	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;
	
};
