// Fill out your copyright notice in the Description page of Project Settings.


#include "C_DecreaseBreathVolume.h"
#include "Components/BoxComponent.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "MyProject/UI/C_PlayerHUD2.h"

// Sets default values
AC_DecreaseBreathVolume::AC_DecreaseBreathVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BreathVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Breath Volume"));
	BreathVolume->SetRelativeScale3D(FVector(5.0f));

	//RootComponent = BreathVolume;

	TimeBeforeDrowning = 5.0f;

	RateOfBreath = 1.0f;


	//Sets up collision for the box component
	BreathVolume->OnComponentBeginOverlap.AddDynamic(this, &AC_DecreaseBreathVolume::OnOverlapBegin);
	BreathVolume->OnComponentEndOverlap.AddDynamic(this, &AC_DecreaseBreathVolume::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AC_DecreaseBreathVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_DecreaseBreathVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_DecreaseBreathVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if(OtherActor == PlayerCharacter && OtherComp == PlayerCharacter->HeadCollisionComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("Breath is: %f"), PlayerCharacter->Breath);

		bShouldDecreaseBreath = true;
		GetWorldTimerManager().SetTimer(DecreaseBreathHandle, this, &AC_DecreaseBreathVolume::DecreaseBreath, RateOfBreath, true);
		GetWorldTimerManager().ClearTimer(RegenBreathHandle);

		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (PlayerHUD && PlayerCharacter->Breath == 100.0f)
		{
			//PlayerHUD->HUDBreathBarVisible();
			PlayerHUD->PlayBreathBarFadeInAnimationHUD();
			bHasFadedOut = false;
		}
	}
}

void AC_DecreaseBreathVolume::DecreaseBreath()
{
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	PlayerCharacter->Breath -= 10.0f;

	//Clamps Breath
	if(PlayerCharacter->Breath <= 0.0f)
	{
		PlayerCharacter->Breath = 0.0f;
		PlayerCharacter->DamageOverTime();
		//UE_LOG(LogTemp, Log, TEXT("Start Damage over time"));
		GetWorldTimerManager().ClearTimer(DecreaseBreathHandle);
	}
}


void AC_DecreaseBreathVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == PlayerCharacter && OtherComp == PlayerCharacter->HeadCollisionComponent)
	{
		bShouldDecreaseBreath = false;
		GetWorldTimerManager().SetTimer(RegenBreathHandle, this, &AC_DecreaseBreathVolume::RegenBreath, 1.0f, true);
		GetWorldTimerManager().ClearTimer(DecreaseBreathHandle);
		PlayerCharacter->StopDamageOverTime();
		
		UE_LOG(LogTemp, Log, TEXT("Breath is: %f"), PlayerCharacter->Breath);

		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (PlayerHUD)
		{
			if(PlayerCharacter->Breath == 100.0f)
			{
				//PlayerHUD->HUDBreathBarInVisible();
				PlayerHUD->PlayBreathBarFadeOutAnimationHUD();
				bHasFadedOut = true;
			}
		}
	}
}


void AC_DecreaseBreathVolume::RegenBreath()
{
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerCharacter->Breath += 5.0f;
	if(PlayerCharacter->Breath >= 100.0f)
	{
		PlayerCharacter->Breath = 100.0f;
	}

	if(PlayerCharacter->Breath == 100.0f)
	{
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (PlayerHUD && !bHasFadedOut)
		{
			//PlayerHUD->HUDBreathBarVisible();
			PlayerHUD->PlayBreathBarFadeOutAnimationHUD();
			GetWorldTimerManager().ClearTimer(RegenBreathHandle);
		}
	}
}

void AC_DecreaseBreathVolume::UpdateBreathVisibility()
{
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if(PlayerCharacter->Breath != 100.0f)
	{
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (PlayerHUD)
		{
			//PlayerHUD->HUDBreathBarVisible();
			PlayerHUD->PlayBreathBarFadeInAnimationHUD();
		}
	}

	if (PlayerCharacter->Breath == 100.0f)
	{
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (PlayerHUD)
		{
			//PlayerHUD->HUDBreathBarInVisible();
			GetWorldTimerManager().ClearTimer(RegenBreathHandle);
			PlayerHUD->PlayBreathBarFadeOutAnimationHUD();
		}
	}
}