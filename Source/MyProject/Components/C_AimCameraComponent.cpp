// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AimCameraComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UC_AimCameraComponent::UC_AimCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AimCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("AimCameraComponent"));
	//AimCameraComp->SetupAttachment(CrossbowRef, "rootSocket");
	AimCameraComp->bUsePawnControlRotation = false;
	AimCameraComp->bAutoActivate = false;
}


// Called when the game starts
void UC_AimCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_AimCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

