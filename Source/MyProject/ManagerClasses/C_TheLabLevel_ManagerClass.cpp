
#include "C_TheLabLevel_ManagerClass.h"
#include "MyProject/Misc/C_WarningLight.h"
#include "MyProject/Misc/C_ReactorBeam.h"
#include "MyProject/Misc/C_BlackHole.h"
#include "EngineUtils.h"
#include "kismet/GameplayStatics.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/Quest System/C_BaseQuest.h"

AC_TheLabLevel_ManagerClass::AC_TheLabLevel_ManagerClass()
{
	PrimaryActorTick.bCanEverTick = true;

	BeamCounter = 0;

	TimeBetweenSequences = 3;
}

void AC_TheLabLevel_ManagerClass::BeginPlay()
{
	Super::BeginPlay();
}

void AC_TheLabLevel_ManagerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_TheLabLevel_ManagerClass::Update()
{
	// This for loop check will check if all manager classes in the array have been completed via the bIsComplete bool in the base class.
	// If they have will Log.

	bool IsAllOn;

	bool Allon = true;
	for (AC_BaseManagerClass* x : ManagerArray)
	{
		if(!x->bIsComplete)
		{
			Allon = false;
			//UE_LOG(LogTemp, Warning, TEXT("All puzzles not completed"));
			break;
		}
	}

	IsAllOn = Allon;

	// If all puzzles are complete...
	if(IsAllOn == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("All puzzles completed"));

		
	}

	if(MainQuest && MainQuest->bIsCompleted)
	{
		UE_LOG(LogTemp, Warning, TEXT("MAIN QUEST COMPLETE"));

		AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (HUD)
		{
			HUD->HideAllElements();
		}

		ChangeLighting();

		for (auto i : WarningLightArray)
		{
			i->StartPulse();
		}

		PuzzlesAreComplete();

		AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		PlayerCharacter->bCanInteract = false;

		FTimerHandle FirstBeamHandle;
		GetWorldTimerManager().SetTimer(FirstBeamHandle, this, &AC_TheLabLevel_ManagerClass::ActivateFirstBeam, 1.0f, false);
	}
}

void AC_TheLabLevel_ManagerClass::ActivateFirstBeam()
{
	CoreBeamArray[0]->BecomeVisible();
	PlayCameraShake();
	GetWorldTimerManager().SetTimer(ActivateBeamHandle, this, &AC_TheLabLevel_ManagerClass::ActivateSecondBeam, 3.0f, true);
}

void AC_TheLabLevel_ManagerClass::ActivateSecondBeam()
{
	switch (BeamCounter)
	{
	case 0:
		BeamCounter++;
		PlayCameraShake();
		CoreBeamArray[1]->BecomeVisible();
		//UE_LOG(LogTemp, Warning, TEXT("first time"));
		break;

	case 1:
		BeamCounter++;
		PlayCameraShake();
		CoreBeamArray[2]->BecomeVisible();
		//UE_LOG(LogTemp, Warning, TEXT("second time"));
		break;

	case 2:
		//UE_LOG(LogTemp, Warning, TEXT("third time"));

		StartBeamCorruption();
		GetWorldTimerManager().ClearTimer(ActivateBeamHandle);
		break;
	}
}


void AC_TheLabLevel_ManagerClass::SpawnBlackHole()
{
	for (auto x : PhysicsActorsArray)
	{
		for (auto i : x->GetComponents())
		{
			UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(i);

			UE_LOG(LogTemp, Warning, TEXT("GOT COMPS"));

			if (SM)
			{
				UE_LOG(LogTemp, Warning, TEXT("CAST SUCCESS"));

				SM->SetGenerateOverlapEvents(true);
				SM->SetMobility(EComponentMobility::Movable);
				SM->SetSimulatePhysics(true);
				SM->AddForce(FVector(900000, 900000, 900000));
			}

			USkeletalMeshComponent* SK = Cast<USkeletalMeshComponent>(i);

			if (SK)
			{
				SK->SetGenerateOverlapEvents(true);
				SK->SetMobility(EComponentMobility::Movable);
				SK->SetSimulatePhysics(true);
				SK->AddForce(FVector(500000, 500000, 500000));
			}
		}
	}

	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		PlayerController->ClientPlayCameraShake(BlackHoleCameraShake);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector BHSpawnLocation = BlackHoleSpawnPoint->GetActorLocation();
	FRotator BHSpawnRotation = BlackHoleSpawnPoint->GetActorRotation();

	BlackHole = GetWorld()->SpawnActor<AC_BlackHole>(BlackHoleClass, BHSpawnLocation, BHSpawnRotation, SpawnParams);
}

void AC_TheLabLevel_ManagerClass::PlayCameraShake()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		PlayerController->ClientPlayCameraShake(CameraShake);
	}
}

// Starts beam corruption sequence 
void AC_TheLabLevel_ManagerClass::StartBeamCorruption()
{
	for (auto i : CoreBeamArray)
	{
		i->BeginCorruption();
	}
}

void AC_TheLabLevel_ManagerClass::StartMinorBeamCorruption()
{
	for (auto i : MinorBeamArray)
	{
		i->MinorBeamSetup();
	}

	for(auto i : CoreBeamArray)
	{
		i->StartCorruptionMajorBeams();
	}
}
