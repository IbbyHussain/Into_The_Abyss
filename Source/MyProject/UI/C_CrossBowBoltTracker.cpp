// Fill out your copyright notice in the Description page of Project Settings.


#include "C_CrossBowBoltTracker.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"

UC_CrossBowBoltTracker::UC_CrossBowBoltTracker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_CrossBowBoltTracker::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::HitTestInvisible);

	// shows correct number of bolts when constructed
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UpdateNumberOfBolts(PlayerCharacter->Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts);
}

void UC_CrossBowBoltTracker::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UC_CrossBowBoltTracker::UpdateNumberOfBolts(int32 NumOfBolts)
{
	FString NumOfBoltsString = FString::FromInt(NumOfBolts);
	CrossbowBoltTracker->SetText(FText::FromString(NumOfBoltsString + " Bolts"));
}

