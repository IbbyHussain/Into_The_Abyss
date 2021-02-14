// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Crossbow.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "MyProject/Weapons/Crossbow/C_DummyBolt.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "MyProject/C_PlayerCharacter.h"

// Saving
#include "MyProject/Misc/C_BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"

AC_Crossbow::AC_Crossbow()
{
	PrimaryActorTick.bCanEverTick = true;

	//NumberOfBolts = 65;

	CrossbowboltSocket = ("CrossbowboltSocket");

	DummyBoltSocket = ("DummyBoltSocket");

	// Dummy Bolt timeline

	SlideTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("SlideTimeline"));

	SlideInterpFunction.BindUFunction(this, FName("SlideTimelineFloatReturn"));

}


void AC_Crossbow::BeginPlay()
{
	Super::BeginPlay();

	//Sets the values of the slide timeline
	if (FSlideCurve)
	{
		SlideTimeline->AddInterpFloat(FSlideCurve, SlideInterpFunction, FName("Bravo"));
		SlideTimeline->SetLooping(false);
	}
}

void AC_Crossbow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Crossbow::UpdateNumberofBolts(int32 Num)
{
	AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUD->UpdateCrossbowBoltTracker(BoltIcon, Num);
}


void AC_Crossbow::SpawnBolt(FVector EndLocation)
{
	// This will also fire the bolt has it starts moving when spawned via projectile movement component

	FActorSpawnParameters SpawnParams;

	// Set the bolt's transform which is at the socket location
	FTransform CrossbowTransform = MeshComp->GetSocketTransform(CrossbowboltSocket, ERelativeTransformSpace::RTS_World);
	FVector CrossbowSpawnLocation = CrossbowTransform.GetLocation();

	// This allows the bolt to fire towards the centre of teh screen as it will use the hit reult as final location
	FRotator CrossbowSpawnRotation = UKismetMathLibrary::FindLookAtRotation(CrossbowSpawnLocation, EndLocation);

	// Spawn the bolt
	Crossbowbolt = GetWorld()->SpawnActor<AC_Crossbowbolt>(CrossbowboltClass, CrossbowSpawnLocation, CrossbowSpawnRotation, SpawnParams);
}

void AC_Crossbow::SpawnBoltAI(FVector EndLoc)
{
	FActorSpawnParameters SpawnParams;

	// Set the bolt's transform which is at the socket location
	FTransform CrossbowTransform = MeshComp->GetSocketTransform(CrossbowboltSocket, ERelativeTransformSpace::RTS_World);
	FVector CrossbowSpawnLocation = CrossbowTransform.GetLocation();

	// This allows the bolt to fire towards the centre of teh screen as it will use the hit reult as final location
	FRotator CrossbowSpawnRotation = UKismetMathLibrary::FindLookAtRotation(CrossbowSpawnLocation, EndLoc);

	// Spawn the bolt
	Crossbowbolt = GetWorld()->SpawnActor<AC_Crossbowbolt>(AICrossbowboltClass, CrossbowSpawnLocation, CrossbowSpawnRotation, SpawnParams);
}

void AC_Crossbow::SpawnDummybolt(FName SocketName, TSubclassOf<AC_DummyBolt> DummyClass)
{
	FActorSpawnParameters SpawnParams;

	FTransform DummyBoltTransfrom = MeshComp->GetSocketTransform(SocketName, ERelativeTransformSpace::RTS_World);
	FVector DummyBoltLocation = DummyBoltTransfrom.GetLocation();
	FRotator DummyBoltRotation = DummyBoltTransfrom.GetRotation().Rotator();

	DummyBolt = GetWorld()->SpawnActor<AC_DummyBolt>(DummyClass, DummyBoltLocation, DummyBoltRotation, SpawnParams);
	DummyBolt->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepWorldTransform, SocketName);
	
}

void AC_Crossbow::ReloadCrossbow()
{
	PlayTimeline();
}

void AC_Crossbow::DestroyDummyBolt()
{
	if(DummyBolt)
	{
		DummyBolt->Destroy();
	}
}

void AC_Crossbow::SlideTimelineFloatReturn(float Value)
{
	if(DummyBolt)
	{
		float ActorX = DummyBolt->GetActorLocation().X;
		float ActorY = DummyBolt->GetActorLocation().Y;
		DummyBolt->SetActorLocation(FMath::Lerp(MeshComp->GetSocketLocation(DummyBoltSocket), MeshComp->GetSocketLocation(CrossbowboltSocket), Value));
		DummyBolt->SetActorRotation(MeshComp->GetSocketRotation(CrossbowboltSocket)); // Fixes issue where bolt would rotate in random directions
	}
}


void AC_Crossbow::PlayTimeline()
{
	SlideTimeline->PlayFromStart();
}

// Saves the current value of all bolt types
void AC_Crossbow::SaveBolts()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->NumberOfSteelBolts = BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts;
		SaveGameInstance->NumberOfCopperBolts = BoltsArray[1]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts;
		SaveGameInstance->NumberOfCrystalBolts = BoltsArray[2]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts;
		SaveGameInstance->NumberOfFlareBolts = BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts;

		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 0))
		{
			UE_LOG(LogTemp, Log, TEXT("Save Succeeded (crossbowbolts)"));
		}
	}
}

void AC_Crossbow::LoadBolts()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("TestSaveSlot"), 0)))
	{
		BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = LoadedGame->NumberOfSteelBolts;
		BoltsArray[1]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = LoadedGame->NumberOfCopperBolts;
		BoltsArray[2]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = LoadedGame->NumberOfCrystalBolts;
		BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = LoadedGame->NumberOfFlareBolts;

		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %d"), LoadedGame->NumberOfSteelBolts);
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %d"), LoadedGame->NumberOfCopperBolts);
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %d"), LoadedGame->NumberOfCrystalBolts);
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %d"), LoadedGame->NumberOfFlareBolts);
	}
}

// sets all bolts back to default, then saves them
void AC_Crossbow::ResetBolts()
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		// Set data on the savegame object.

		BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = 3;
		BoltsArray[1]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = 3;
		BoltsArray[2]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = 3;
		BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = 3;

		SaveBolts();
	}
}
