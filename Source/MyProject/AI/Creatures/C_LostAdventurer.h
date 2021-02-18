// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "C_LostAdventurer.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AC_LostAdventurer : public AC_MeleeAI
{
	GENERATED_BODY()

	AC_LostAdventurer();
	
private:

	virtual void ChangeAIColour() override;

public:

	bool bLAcanAttack;

	void Attack(USkeletalMeshComponent* SKMesh, float Damage, FName StartSocket, FName EndSocket);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Crawler")
	bool bIsCrawler;

};
