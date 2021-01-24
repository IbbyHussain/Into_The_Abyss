// Fill out your copyright notice in the Description page of Project Settings.


#include "C_FlareBoltPickupItemWidget.h"
#include "MyProject/AI/C_BaseTraderAI.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/Button.h"
#include "MyProject/C_MainGameInstance.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "MyProject/GameObjects/SkeletalMeshs/Weapons/C_Crossbow.h"
#include "MyProject/Weapons/Crossbow/C_Crossbowbolt.h"
#include "MyProject/Weapons/Crossbow/C_DummyBolt.h"

void UC_FlareBoltPickupItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Frame skip
	FTimerHandle FrameHandle;
	GetWorld()->GetTimerManager().SetTimer(FrameHandle, this, &UC_FlareBoltPickupItemWidget::ConstructChecks, 0.02f, false);

	PurchaseButton->OnClicked.AddDynamic(this, &UC_FlareBoltPickupItemWidget::PurchaseFlareBolt);
}

void UC_FlareBoltPickupItemWidget::ConstructChecks()
{
	ShouldDisablePurchaseButtonBolts(TraderAIPTR->FlareBoltPickupAmount, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->NumberOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->MaxAmountOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->Price);
	UpdateItem();
}

void UC_FlareBoltPickupItemWidget::UpdateItem()
{
	NumberOfItems.Empty();
	NumberOfItems.AppendInt(TraderAIPTR->FlareBoltPickupAmount);
	TXTItemQuantity->SetText(FText::FromString(NumberOfItems));
}

void UC_FlareBoltPickupItemWidget::PurchaseFlareBolt()
{
	Purchase(TraderAIPTR->FlareBoltPickupAmount, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->Price);

	if (PlayerCharacter->Crossbow.CurrentDummyBolt == PlayerCharacter->Crossbow.CrossbowObject->DummyBoltsArray[3])
	{
		if (PlayerCharacter->Crossbow.CurrentBolt->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts == 0 && PlayerCharacter->CombatState == ECombatState::RANGED)
		{
			PlayerCharacter->SpawnDummyBolt();
		}
	}

	// increments bolts and saves it.
	PlayerCharacter->UpdateNumberOfBolts(PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->NumberOfBolts);

	UpdateItem();

	// Ensures that the number of bolts never exceeds the max amount
	if (PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts >= PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->MaxAmountOfBolts)
	{
		PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject<AC_Crossbowbolt>()->NumberOfBolts = PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
			<AC_Crossbowbolt>()->MaxAmountOfBolts;
	}

	ShouldDisablePurchaseButtonBolts(TraderAIPTR->FlareBoltPickupAmount, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->NumberOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->MaxAmountOfBolts, PlayerCharacter->Crossbow.CrossbowObject->BoltsArray[3]->GetDefaultObject
		<AC_Crossbowbolt>()->Price);
}


