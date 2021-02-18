// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LostAdventurer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/MyProject.h"
#include "MyProject/C_PlayerCharacter.h"

AC_LostAdventurer::AC_LostAdventurer()
{
	bLAcanAttack = true;
}

void AC_LostAdventurer::ChangeAIColour()
{
	Super::ChangeAIColour();

	UE_LOG(LogTemp, Error, TEXT("Lost adventurer change colours tyes"));

	ChangeColours(true, SkinColourMaterial.SkinMaterialArray, 2, 1);
	ChangeColours(true, ClothingColourMaterial.ClothingMaterialArray, 2, 0);
}

void AC_LostAdventurer::Attack(USkeletalMeshComponent* SKMesh, float Damage, FName StartSocket, FName EndSocket)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack player"));


	// Get the start and end location of the sphere trace (two sockets that are the length of the sword)
	FVector StartLocation = GetMesh()->GetSocketLocation(StartSocket); 
	FVector EndLocation = GetMesh()->GetSocketLocation(EndSocket);

	FHitResult HitResult;

	TArray<AActor*> ActorsIgnored;
	ActorsIgnored = { this };

	// Convert the collision type to standard collision channel
	ETraceTypeQuery Trace6 = UEngineTypes::ConvertToTraceType(ECollisionChannel::COLLISION_AIMELEEDETECTION);

	bool bHits = UKismetSystemLibrary::SphereTraceSingle(SKMesh, StartLocation, EndLocation, 35.0f, Trace6, false, ActorsIgnored, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green);

	AC_PlayerCharacter* PlayerCharacterPTR = Cast<AC_PlayerCharacter>(HitResult.GetActor());

	if (bHits && PlayerCharacterPTR && bLAcanAttack)
	{
		UE_LOG(LogTemp, Error, TEXT("Hit player"))
		PlayerCharacterPTR->ApplyDamageToPlayer(Damage);
		bLAcanAttack = false;
	}
}