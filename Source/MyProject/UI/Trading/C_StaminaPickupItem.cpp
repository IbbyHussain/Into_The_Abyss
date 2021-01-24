
#include "C_StaminaPickupItem.h"
#include "MyProject/AI/C_BaseTraderAI.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/Button.h"
#include "MyProject/C_MainGameInstance.h"
#include "Components/TextBlock.h"

UC_StaminaPickupItem::UC_StaminaPickupItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_StaminaPickupItem::NativeConstruct()
{
	Super::NativeConstruct();

	// Frame skip
	FTimerHandle FrameHandle;
	GetWorld()->GetTimerManager().SetTimer(FrameHandle, this, &UC_StaminaPickupItem::ConstructChecks, 0.02f, false);

	PurchaseButton->OnClicked.AddDynamic(this, &UC_StaminaPickupItem::PurchaseStamina);
}

void UC_StaminaPickupItem::ConstructChecks()
{
	ShouldDisablePurchaseButton(TraderAIPTR->StaminaPickupAmount, PlayerCharacter->Stamina); 
	UpdateItem();
}

void UC_StaminaPickupItem::UpdateItem()
{
	NumberOfItems.Empty();
	NumberOfItems.AppendInt(TraderAIPTR->StaminaPickupAmount);
	TXTItemQuantity->SetText(FText::FromString(NumberOfItems));
}

void UC_StaminaPickupItem::PurchaseStamina()
{
	// Allows the player to buy the item first 
	AttributePurchase(PlayerCharacter->Stamina, 10.0f, TraderAIPTR->StaminaPickupAmount);

	UpdateItem();

	// then will disbale button if after that the stamina is full
	if (PlayerCharacter->Stamina >= 100.0f )
	{
		PlayerCharacter->Stamina = 100.0f;
	}

	ShouldDisablePurchaseButton(TraderAIPTR->StaminaPickupAmount, PlayerCharacter->Stamina);

}