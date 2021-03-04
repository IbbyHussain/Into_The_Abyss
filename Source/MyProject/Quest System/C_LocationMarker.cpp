// Fill out your copyright notice in the Description page of Project Settings.


#include "C_LocationMarker.h"
#include "Components/SphereComponent.h"
#include "MyProject/Quest System/C_BaseQuest.h"

AC_LocationMarker::AC_LocationMarker()
{
	CollisonComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collison comp"));
}

void AC_LocationMarker::BeginPlay()
{
	Super::BeginPlay();

	CollisonComp->OnComponentBeginOverlap.AddDynamic(this, &AC_LocationMarker::OnOverlapBegin);
}
void AC_LocationMarker::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// location reached delegate here 
	Quest->CheckLocationObjectiveDelegate.Broadcast(this);
}



