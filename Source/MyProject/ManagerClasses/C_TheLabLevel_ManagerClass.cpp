#include "C_TheLabLevel_ManagerClass.h"
#include "MyProject/Misc/C_WarningLight.h"
#include "MyProject/Misc/C_ReactorBeam.h"
#include "EngineUtils.h"

AC_TheLabLevel_ManagerClass::AC_TheLabLevel_ManagerClass()
{
	PrimaryActorTick.bCanEverTick = true;
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
			UE_LOG(LogTemp, Warning, TEXT("All puzzles not completed"));
			break;
		}
	}

	IsAllOn = Allon;

	if(IsAllOn == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("All puzzles completed"));

		for (auto i : WarningLightArray)
		{
			i->StartPulse();
		}

		// Core beams become corrupted
		for (auto i : CoreBeamArray)
		{
			i->BecomeVisible();
			i->BeginCorruption();
		}

		// Core beams become corrupted
		for (auto i : CoreBeamArray)
		{
			i->BecomeVisible();
			i->BeginCorruption();
		}

		for(auto i : MinorBeamArray)
		{
			i->MinorBeamSetup();
		}

	}
}
