#include "C_Ability2.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "MyProject/AI/C_BaseAI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AC_Ability2::AC_Ability2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = rootComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	BoxComp->SetupAttachment(RootComponent);

	Ability2Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Comp"));
	Ability2Effect->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f), false, false);
	Ability2Effect->SetupAttachment(RootComponent);

	// Cannot be used in constructor causes packaged build to crash
	//Ability2Effect->SetVariableFloat(FName("Life"), 1.0f);

	// Material Fade Out
	MaterialFadeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Material Fade Timeline"));
	MaterialFadeInterpFunction.BindUFunction(this, FName("MaterialFadeTimelineFloatReturn"));

}

void AC_Ability2::BeginPlay()
{
	Super::BeginPlay();
	
	//Sets the Life Variable to 1 so that the particles are generated 
	Ability2Effect->SetNiagaraVariableFloat(FString("Opacity"), 1.0f);
	Ability2Effect->SetVariableFloat(FName("Life"), 1.0f);

	//Timeline setup
	if (FMaterialFadeCurve)
	{
		MaterialFadeTimeline->AddInterpFloat(FMaterialFadeCurve, MaterialFadeInterpFunction, FName("alpha"));
		MaterialFadeTimeline->SetLooping(false);
	}
}

void AC_Ability2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Ability2::ParticleFadeOut()
{
	MaterialFadeTimeline->Play(); //Access violation reading location
}

void AC_Ability2::DeSpawnParticleEffect()
{
	//Destroys particle effect
	Ability2Effect->SetVariableFloat(FName("Life"), 0.0f);
	Destroy();
}

void AC_Ability2::MaterialFadeTimelineFloatReturn(float Alpha)
{
	//Makes the glow effect fade out
	Ability2Effect->SetNiagaraVariableFloat(FString("Opacity"), Alpha);
}

// Destroyes this actor
void AC_Ability2::DestroyThis()
{
	Destroy();
}