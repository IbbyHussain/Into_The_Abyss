// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ExitArea.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_UW_EKeyHint.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
AC_ExitArea::AC_ExitArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComp;
	BoxComp->SetRelativeScale3D(FVector(2.5f));
	BoxComp->SetHiddenInGame(false);

	//Sets up collision for the box component
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AC_ExitArea::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AC_ExitArea::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AC_ExitArea::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AC_ExitArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AC_PlayerCharacter* PlayerRef = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

//On Overlap Begin
void AC_ExitArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_PlayerCharacter* PlayerRef = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if(OtherActor == PlayerRef && (OtherActor != this && OtherComp == PlayerRef->GetCapsuleComponent())) //&& OtherComp == PlayerRef->BoxComp
	{
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if(PlayerHUD)
		{
			PlayerHUD->SetEKeyHintText("Climb");
			PlayerHUD->MakeEKeyHintVisible();
		}
		PlayerRef->bCanExit = true;
	}
}

//On Overlap End
void AC_ExitArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AC_PlayerCharacter* PlayerRef = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == PlayerRef && (OtherActor != this && OtherComp == PlayerRef->GetCapsuleComponent())) //&& OtherComp == PlayerRef->BoxComp
	{
		//Cast to the HUD 
		AC_PlayerHUD2* PlayerHUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (PlayerHUD)
		{
			PlayerHUD->MakeEKeyHintInVisible();
		}
		PlayerRef->bCanExit = false;
	}
	
}

void AC_ExitArea::EKeyPressed()
{
	// set the players location here then call it in the player file
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Character->SetActorLocation(ExitAreaActorLocation);
}