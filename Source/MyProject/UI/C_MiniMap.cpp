// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MiniMap.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "MyProject/UI/C_PlayerIcon.h"
#include "MyProject/UI/C_PointOfIntrest.h"
#include "MyProject/Components/C_POIComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"


UC_MiniMap::UC_MiniMap(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_MiniMap::NativeConstruct()
{
	Super::NativeConstruct();

	Instance = GetWorld()->GetParameterCollectionInstance(Collection);
	Instance->SetScalarParameterValue(FName("Dimensions"), Dimensions);
	Instance->SetScalarParameterValue(FName("Zoom"), Zoom);

	DynamicMaterial = Map->GetDynamicMaterial();
	DynamicMaterial->SetTextureParameterValue(FName("CurrentMap"), MapTexture);

	//Creates the player icon class
	if (PlayerIcon)
	{
		PlayerIconWidget = CreateWidget<UC_PlayerIcon>(GetWorld(), PlayerIcon);
		if (PlayerIconWidget)
		{
			//Adds the widget above the map
			SlotRef= MapOverlay->AddChildToOverlay(PlayerIconWidget);
			//Sets it alignment to the center
			SlotRef->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			SlotRef->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		}
	}
	
}

void UC_MiniMap::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	if(UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		//Sets the players X and Y co-ordinates to the Player icon's X and Y co-ordinates.
		float X = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation().X;
		float Y = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation().Y;

		Instance->SetScalarParameterValue(FName("X"), X);
		Instance->SetScalarParameterValue(FName("Y"), Y);
		Instance->SetScalarParameterValue(FName("Zoom"), Zoom);
	}
}

UC_PointOfIntrest* UC_MiniMap::AddPOI(AActor* Actor)
{
	UE_LOG(LogTemp, Log, TEXT("Added POI widget!!!"));
	
	POIWidget = CreateWidget<UC_PointOfIntrest>(GetWorld(), POI);
	if (POIWidget)
	{
		POIWidget->Owner = Actor;
		MapOverlaySlot = MapOverlay->AddChildToOverlay(POIWidget);
		MapOverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		MapOverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		return POIWidget;
	}
	

	return POIWidget;
}

float UC_MiniMap::CalculateZoom()
{
	return Zoom * (Dimensions / 300.0f);
}