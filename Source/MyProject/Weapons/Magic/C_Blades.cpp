// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Blades.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "MyProject/AI/C_BaseAI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AC_Blades::AC_Blades()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = rootComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	BoxComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AC_Blades::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Blades::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

