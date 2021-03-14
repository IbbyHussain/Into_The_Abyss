#include "C_TheLabLevel_ManagerClass.h"
#include "MyProject/Misc/C_WarningLight.h"
#include "MyProject/Misc/C_ReactorBeam.h"
#include "MyProject/Misc/C_BlackHole.h"
#include "EngineUtils.h"

AC_TheLabLevel_ManagerClass::AC_TheLabLevel_ManagerClass()
{
	PrimaryActorTick.bCanEverTick = true;

	BeamCounter = 0;

	TimeBetweenSequences = 3;
}

void AC_TheLabLevel_ManagerClass::BeginPlay()
{
	Super::BeginPlay();

	CoreBeamArray[0]->BecomeVisible();
	GetWorldTimerManager().SetTimer(ActivateBeamHandle, this, &AC_TheLabLevel_ManagerClass::ActivateSecondBeam, 3.0f, true);

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
				SM->AddForce(FVector(10000, 10000, 10000));
			}

			USkeletalMeshComponent* SK = Cast<USkeletalMeshComponent>(i);

			if(SK)
			{
				SK->SetGenerateOverlapEvents(true);
				SK->SetMobility(EComponentMobility::Movable);
				SK->SetSimulatePhysics(true);
				SK->AddForce(FVector(10000, 10000, 10000));
			}
		}

	}
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
		//UE_LOG(LogTemp, Warning, TEXT("All puzzles completed"));

		for (auto i : WarningLightArray)
		{
			i->StartPulse();
		}

		CoreBeamArray[0]->BecomeVisible();
		GetWorldTimerManager().SetTimer(ActivateBeamHandle, this, &AC_TheLabLevel_ManagerClass::ActivateSecondBeam, TimeBetweenSequences, true);

		//SpawnBlackHole();
		// Core beams become corrupted
		/*for (auto i : CoreBeamArray)
		{
			i->BecomeVisible();
			i->BeginCorruption();
		}*/

		/*for(auto i : MinorBeamArray)
		{
			i->MinorBeamSetup();
		}*/

	}
}

void AC_TheLabLevel_ManagerClass::ActivateSecondBeam()
{
	switch (BeamCounter)
	{
	case 0:
		BeamCounter++;
		CoreBeamArray[1]->BecomeVisible();
		//UE_LOG(LogTemp, Warning, TEXT("first time"));
		break;

	case 1:
		BeamCounter++;
		CoreBeamArray[2]->BecomeVisible();
		//UE_LOG(LogTemp, Warning, TEXT("second time"));
		break;

	case 2:
		//UE_LOG(LogTemp, Warning, TEXT("third time"));

		for (auto i : CoreBeamArray)
		{
			i->BeginCorruption();
		}

		for(auto i : MinorBeamArray)
		{
			i->MinorBeamSetup();
		}

		FTimerHandle BlackHoleHandle;
		GetWorldTimerManager().SetTimer(BlackHoleHandle, this, &AC_TheLabLevel_ManagerClass::SpawnBlackHole, 6.0f, false);

		GetWorldTimerManager().ClearTimer(ActivateBeamHandle);

		break;
	}
}


void AC_TheLabLevel_ManagerClass::SpawnBlackHole()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector BHSpawnLocation = BlackHoleSpawnPoint->GetActorLocation();
	FRotator BHSpawnRotation = BlackHoleSpawnPoint->GetActorRotation();

	BlackHole = GetWorld()->SpawnActor<AC_BlackHole>(BlackHoleClass, BHSpawnLocation, BHSpawnRotation, SpawnParams);


}