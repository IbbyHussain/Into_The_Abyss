// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ChestActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "TimerManager.h"
#include "MyProject/GameObjects/StaticMeshs/Interactables/Pickups/C_Pickup.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SkeletalPickupBase.h"

AC_ChestActorBase::AC_ChestActorBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PastMesh->SetupAttachment(Root);
	FutureMesh->SetupAttachment(Root);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComp->SetupAttachment(Root);

	// The mesh for the glow effect
	PastPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Past Plane"));
	PastPlane->SetupAttachment(Root);

	FuturePlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Future Plane"));
	FuturePlane->SetupAttachment(Root);
	FuturePlane->SetVisibility(false);

	// Parents the chest lid collision box to the socket so that it move with it.
	ChestLid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chest Lid"));
	ChestLid->SetupAttachment(Root);
	ChestLid->SetVisibility(false);

	ChestLidSocketName = ("ChestLidSocket");
	PickupSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PickupSpawnlocation"));
	PickupSpawnLocation->SetupAttachment(Root);

	// Dynamic material fade
	MaterialFadeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Material Fade Timeline"));
	MaterialFadeInterpFunction.BindUFunction(this, FName("MaterialFadeTimelineFloatReturn"));

	bShowEKeyHint = true;

	bCanOpenChest = true;

	bOverlapping = false;
}

void AC_ChestActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_ChestActorBase::BeginPlay()
{
	Super::BeginPlay();

	// References 
	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	//Attaches this to the mesh so that it moves with it
	ChestLid->AttachToComponent(PastMesh, FAttachmentTransformRules::KeepWorldTransform, ChestLidSocketName);

	//Creates dynamic material
	DynamicChestMaterialGlow = UMaterialInstanceDynamic::Create(ChestMaterialGlow, this);
	PastPlane->SetMaterial(0, DynamicChestMaterialGlow);
	FuturePlane->SetMaterial(0, DynamicChestMaterialGlow);

	//Timeline setup
	if (FMaterialFadeCurve)
	{
		MaterialFadeTimeline->AddInterpFloat(FMaterialFadeCurve, MaterialFadeInterpFunction, FName("alpha"));
		MaterialFadeTimeline->SetLooping(false);
	}
}


//Checks if the player is overlapping with the box collision
bool AC_ChestActorBase::OverlappingBoxCollision()
{
	if (BoxComp->IsOverlappingActor(PlayerCharacter))
	{
		bOverlapping = true;
		return bOverlapping;
	}

	else
	{
		bOverlapping = false;
		return bOverlapping;
	}
}

void AC_ChestActorBase::SpawnPickup(FVector Location, FRotator Rotation)
{
	//Will spawn the pick up when called
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Pickup = GetWorld()->SpawnActor<AC_SkeletalPickupBase>(PickupClass, Location, Rotation, SpawnParams);
}

void AC_ChestActorBase::LaunchPickup()
{
	//Calls the Spawn pickup function then starts timer so that it launches when the chest is opened
	FVector SpawnLocation = PickupSpawnLocation->GetComponentLocation();
	SpawnPickup(SpawnLocation, FRotator::ZeroRotator);
	GetWorldTimerManager().SetTimer(LaunchHandle, this, &AC_ChestActorBase::StartLaunch, 1.5f, false);
}

void AC_ChestActorBase::StartLaunch()
{
	//Allows the pick up to have an arc when it is launched so that it drops infront of the player, doesnt work well with physics assets that are not equal in all dimensions
	float x = Self->PastMesh->GetRightVector().X;
	float y = Self->PastMesh->GetRightVector().Y;
	Pickup->MeshComp->AddForce(FVector(x * 60000.0f, y * 60000.0f, 600000.0f));
}

void AC_ChestActorBase::PlayOpenChestSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ChestOpenSound, GetActorLocation(), GetActorRotation());
	GetWorldTimerManager().ClearTimer(OpenChestSoundHandle);
	MaterialFadeTimeline->Play();
}

void AC_ChestActorBase::MaterialFadeTimelineFloatReturn(float Alpha)
{
	//Makes the glow effect fade out
	DynamicChestMaterialGlow->SetScalarParameterValue(FName("Opacity"), Alpha);
}

void AC_ChestActorBase::FuturePlaneVisibility()
{
	FuturePlane->SetVisibility(true);
	PastPlane->SetVisibility(false);
}

void AC_ChestActorBase::PastPlaneVisibility()
{
	PastPlane->SetVisibility(true);
	FuturePlane->SetVisibility(false);
}

// Interact

// Opens the chest
void AC_ChestActorBase::Interact_Implementation()
{
	if (OverlappingBoxCollision()  && bCanOpenChest)
	{
		RemoveKeyHint_Implementation();
		PastMesh->PlayAnimation(ChestOpenAnimation, false);
		FutureMesh->PlayAnimation(ChestOpenFutureAnimation, false);
		bShowEKeyHint = false;
		bCanOpenChest = false;
		LaunchPickup();
		GetWorldTimerManager().SetTimer(OpenChestSoundHandle, this, &AC_ChestActorBase::PlayOpenChestSound, 0.5, false);
	}
}

// Displays Key hint
void AC_ChestActorBase::DisplayKeyHint_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Press E to ..."));

	if (bShowEKeyHint)
	{
		PlayerCharacter->bCanOpenChest = true;

		if (HUD)
		{
			HUD->SetEKeyHintText("open");
			HUD->MakeEKeyHintVisible();
		}
	}
}

// Displays Key hint
void AC_ChestActorBase::RemoveKeyHint_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Removing -> Press E to ..."));

	if (bShowEKeyHint)
	{
		PlayerCharacter->bCanOpenChest = false;

		if (HUD)
		{
			HUD->MakeEKeyHintInVisible();
		}
	}
}