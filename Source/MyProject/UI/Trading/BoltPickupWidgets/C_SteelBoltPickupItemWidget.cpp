// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SteelBoltPickupItemWidget.h"
#include "MyProject/AI/C_BaseTraderAI.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/Button.h"
#include "MyProject/C_MainGameInstance.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "MyProject/Weapons/Crossbow/C_DummyBolt.h"

void UC_SteelBoltPickupItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//NumberOfBolts = PlayerCharacter->GetCrossbowBolt(0)->NumberOfBolts;
	//MaxNumberOfBolts = PlayerCharacter->GetCrossbowBolt(0)->MaxAmountOfBolts;
	//PriceOfBolt = PlayerCharacter->GetCrossbowBolt(0)->Price;

	// Frame skip
	FTimerHandle FrameHandle;
	GetWorld()->GetTimerManager().SetTimer(FrameHandle, this, &UC_SteelBoltPickupItemWidget::ConstructChecks, 0.02f, true);

	PurchaseButton->OnClicked.AddDynamic(this, &UC_SteelBoltPickupItemWidget::PurchaseHealth);

	CallChildPurchaseButtons.AddDynamic(this, &UC_SteelBoltPickupItemWidget::ConstructChecks);
}

void UC_SteelBoltPickupItemWidget::ConstructChecks()
{
	ShouldDisablePurchaseButtonBolts(TraderAIPTR->SteelBoltPickupAmount, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->NumberOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->MaxAmountOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->Price);
	UpdateItem();
}

// sets the correct amount items for purchase
void UC_SteelBoltPickupItemWidget::UpdateItem()
{
	NumberOfItems.Empty();
	NumberOfItems.AppendInt(TraderAIPTR->SteelBoltPickupAmount);
	TXTItemQuantity->SetText(FText::FromString(NumberOfItems));
}

void UC_SteelBoltPickupItemWidget::PurchaseHealth()
{
	Purchase(TraderAIPTR->SteelBoltPickupAmount, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->Price);

	if (PlayerCharacter->Crossbow.CurrentDummyBolt == PlayerCharacter->Crossbow.CrossbowObject->DummyBoltsArray[0])
	{
		if (PlayerCharacter->Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0 && PlayerCharacter->CombatState == ECombatState::RANGED)
		{
			PlayerCharacter->SpawnDummyBolt();
		}
	}

	// increments bolts and saves it.
	PlayerCharacter->UpdateNumberOfBolts(PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->NumberOfBolts);

	UpdateItem();

	// Ensures that the number of bolts never exceeds the max amount
	if (PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts >= PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->MaxAmountOfBolts)
	{
		PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
			<AC_Crossbowbolt>()->MaxAmountOfBolts;
	}

	ShouldDisablePurchaseButtonBolts(TraderAIPTR->SteelBoltPickupAmount, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->NumberOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->MaxAmountOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[0]->GetDefaultObject
		<AC_Crossbowbolt>()->Price);
}