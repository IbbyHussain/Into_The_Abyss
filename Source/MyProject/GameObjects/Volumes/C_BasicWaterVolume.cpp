// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BasicWaterVolume.h"
#include "EngineUtils.h"
#include "MyProject/AI/C_BaseAI.h"
#include "Components/BoxComponent.h"


AC_BasicWaterVolume::AC_BasicWaterVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));

}


void AC_BasicWaterVolume::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AC_BasicWaterVolume::OnOverlapBegin);
	
}

void AC_BasicWaterVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BoxComp->IsOverlappingActor(AI))
	{
		AI->StopDamage();
	}
}


void AC_BasicWaterVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Log, TEXT("AI ENTERED WATER"));
	UWorld* World = GetWorld();
	for (TActorIterator<AC_BaseAI> It(World, AC_BaseAI::StaticClass()); It; ++It)
	{
		AI = *It;
		if (AI != NULL)
		{
			AIArray.Add(AI);

			if(OtherActor == AI)
			{
				AI->StopDamage();
				AI->DespawnBurningEffects();
				//UE_LOG(LogTemp, Log, TEXT("AI ENTERED WATER AND STOPPED ITS BURNING EFFECT!"));
			}
		}
	}
}


