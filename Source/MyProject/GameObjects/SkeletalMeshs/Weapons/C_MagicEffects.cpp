#include "C_MagicEffects.h"



AC_MagicEffects::AC_MagicEffects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

void AC_MagicEffects::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_MagicEffects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

