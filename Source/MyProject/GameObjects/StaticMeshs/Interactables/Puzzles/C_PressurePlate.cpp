// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PressurePlate.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/GameObjects/StaticMeshs/Interactables/Puzzles/C_MoveableObject.h"
#include "Components/CapsuleComponent.h"

AC_PressurePlate::AC_PressurePlate()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	//Collision Events
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AC_PressurePlate::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &AC_PressurePlate::OnOverlapEnd);
}

void AC_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

	//References
	Player = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	//Dynamic Material
	DynamicPressurePlateMaterial = UMaterialInstanceDynamic::Create(PressurePlateMaterial, MeshComp);
	MeshComp->SetMaterial(0, DynamicPressurePlateMaterial);
	DynamicPressurePlateMaterial->SetScalarParameterValue(FName("Intensity"), 20.0f);
	DynamicPressurePlateMaterial->SetVectorParameterValue(FName("Color"), FColor(255, 0, 0));
}

void AC_PressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bPlayerActivateable)
	{
		if (OtherActor == Player && OtherComp == Player->GetCapsuleComponent())
		{
			Activated();
		}
	}

	else if (OtherActor == MoveableObject && OtherComp == MoveableObject->MeshComp)
	{
		Activated();
	}
}

void AC_PressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bPlayerActivateable)
	{
		if (OtherActor == Player)
		{
			DeActivated();
		}
	}

	else if(OtherActor == MoveableObject && OtherComp == MoveableObject->MeshComp)
	{
		DeActivated();
	}
}

void AC_PressurePlate::Activated()
{
	DynamicPressurePlateMaterial->SetVectorParameterValue(FName("Color"), FColor(0, 255, 0));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PuzzleSound, GetActorLocation());
	bIsActivated = true;
}

void AC_PressurePlate::DeActivated()
{
	DynamicPressurePlateMaterial->SetVectorParameterValue(FName("Color"), FColor(255, 0, 0));
	bIsActivated = false;
}