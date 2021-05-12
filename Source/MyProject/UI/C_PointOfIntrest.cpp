// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PointOfIntrest.h"
#include "Components/Throbber.h"
#include "Kismet/GameplayStatics.h"
#include "Templates/Tuple.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyProject/UI/C_MiniMap.h"
#include "MyProject/Components/C_POIComponent.h"

UC_PointOfIntrest::UC_PointOfIntrest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_PointOfIntrest::NativeConstruct()
{
	Super::NativeConstruct();
}

void UC_PointOfIntrest::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
}

TTuple<float, float> UC_PointOfIntrest::ActorLocation()
{
	if(UGameplayStatics::GetPlayerCharacter(this, 0) && Owner)
	{
		float PlayerX = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation().X;
		float PlayerY = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation().Y;

		
		float OwnerX = Owner->GetActorLocation().X;
		float OwnerY = Owner->GetActorLocation().Y;
		

		float Totalx = PlayerX - OwnerX;
		float Totaly = (PlayerY - OwnerY) * -1.0f;

		return MakeTuple(Totalx, Totaly);
	}

	return MakeTuple(0.0f, 0.0f);
}

float UC_PointOfIntrest ::Returnx()
{
	TTuple<float, float>Getx = ActorLocation();
	return Getx.Get<0>();
}

float UC_PointOfIntrest::Returny()
{
	TTuple<float, float>Gety = ActorLocation();
	return Gety.Get<1>();
}

float UC_PointOfIntrest::FindTheeta(FVector2D PointA, FVector2D PointB)
{
	float X = PointA.X - PointB.X;
	float Y = PointA.Y - PointB.Y;

	float InverseTan = UKismetMathLibrary::DegAtan2(Y, X);

	return InverseTan;
}

FVector2D UC_PointOfIntrest::FindCoordinate(float Radius, float Degrees)
{
	DegCosY = UKismetMathLibrary::DegCos(Degrees);
	DegCosY *= Radius;
	DegCosY *= -1.0f;

	DegSinX = UKismetMathLibrary::DegSin(Degrees);
	DegSinX *= Radius;
	DegSinX *= -1.0f;

	FVector2D Param = FVector2D(DegSinX, DegCosY);

	return Param;
}

FVector2D UC_PointOfIntrest::GetPOILocation(UC_MiniMap* MiniMap)
{
	float rety = Returny();
	float retx = Returnx();

	float retz = MiniMap->CalculateZoom();

	float compx = retx / retz;

	float compy = rety / retz;

	FVector2D ReturnVector2D = FVector2D(compx, compy);

	float Magnitude = ReturnVector2D.Size();

	float Theeta = FindTheeta(FVector2D(0.0f, 0.0f), ReturnVector2D);

	FVector2D Cord = FindCoordinate(Magnitude, Theeta);

	SetRenderTranslation(Cord);

	// When icon is no longer on the minimap, make it hidden. mapsize = 300, 130 || mapsize = 200, 100
	ReturnVector2D.Size() >= 100.0f ? IconImage->SetVisibility(ESlateVisibility::Hidden) : IconImage->SetVisibility(ESlateVisibility::Visible); // Default was 130.0f
		
	return ReturnVector2D;
}

//Updates the POI image 
void UC_PointOfIntrest::UpdateIconImage(UC_POIComponent* POIComponent)
{
	if(IsValid(POIComponent->POIIcon))
	{
		IconImage->SetBrushFromTexture(POIComponent->POIIcon);
		DefaultImage->SetVisibility(ESlateVisibility::Hidden);
	}

	else
	{
		IconImage->SetVisibility(ESlateVisibility::Hidden);
	}
}