// Fill out your copyright notice in the Description page of Project Settings.


#include "C_POIComponent.h"

UC_POIComponent::UC_POIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_POIComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UC_POIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

