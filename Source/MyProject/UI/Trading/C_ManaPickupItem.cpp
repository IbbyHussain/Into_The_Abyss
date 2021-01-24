// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ManaPickupItem.h"
#include "MyProject/AI/C_BaseTraderAI.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/Button.h"
#include "MyProject/C_MainGameInstance.h"
#include "Components/TextBlock.h"

UC_ManaPickupItem::UC_ManaPickupItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_ManaPickupItem::NativeConstruct()
{
	Super::NativeConstruct();

	// Frame skip
	FTimerHandle FrameHandle;
	GetWorld()->GetTimerManager().SetTimer(FrameHandle, this, &UC_ManaPickupItem::ConstructChecks, 0.02f, false);

	PurchaseButton->OnClicked.AddDynamic(this, &UC_ManaPickupItem::PurchaseMana);
}

void UC_ManaPickupItem::ConstructChecks()
{
	ShouldDisablePurchaseButton(TraderAIPTR->ManaPickupAmount, PlayerCharacter->Magic);

	UpdateItem();
}

void UC_ManaPickupItem::UpdateItem()
{
	NumberOfItems.Empty();
	NumberOfItems.AppendInt(TraderAIPTR->ManaPickupAmount);
	TXTItemQuantity->SetText(FText::FromString(NumberOfItems));
}

void UC_ManaPickupItem::PurchaseMana()
{
	// Allows the player to buy the item first 
	AttributePurchase(PlayerCharacter->Magic, 10.0f, TraderAIPTR->ManaPickupAmount);

	UpdateItem();

	// then will disbale button if after that the stamina is full
	if (PlayerCharacter->Magic >= 100.0f)
	{
		PlayerCharacter->Magic = 100.0f;
		//PurchaseButton->SetIsEnabled(false);
	}

	ShouldDisablePurchaseButton(TraderAIPTR->ManaPickupAmount, PlayerCharacter->Magic);
}