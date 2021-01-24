#include "C_BaseManagerClass.h"

AC_BaseManagerClass::AC_BaseManagerClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_BaseManagerClass::BeginPlay()
{
	Super::BeginPlay();
}

void AC_BaseManagerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

