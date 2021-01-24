
#include "C_HealthPickupItemWidget.h"
#include "MyProject/AI/C_BaseTraderAI.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Components/Button.h"
#include "MyProject/C_MainGameInstance.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

UC_HealthPickupItemWidget::UC_HealthPickupItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_HealthPickupItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Frame skip
	FTimerHandle FrameHandle;
	GetWorld()->GetTimerManager().SetTimer(FrameHandle, this, &UC_HealthPickupItemWidget::ConstructChecks, 0.02f, false);

	PurchaseButton->OnClicked.AddDynamic(this, &UC_HealthPickupItemWidget::PurchaseHealth);
}

void UC_HealthPickupItemWidget::ConstructChecks()
{
	ShouldDisablePurchaseButton(TraderAIPTR->HealthPickupAmount, PlayerCharacter->Health);
	UpdateItem();
}

void UC_HealthPickupItemWidget::UpdateItem()
{
	NumberOfItems.Empty();
	NumberOfItems.AppendInt(TraderAIPTR->HealthPickupAmount);
	TXTItemQuantity->SetText(FText::FromString(NumberOfItems));
}

void UC_HealthPickupItemWidget::PurchaseHealth()
{
	AttributePurchase(PlayerCharacter->Health, 10.0f, TraderAIPTR->HealthPickupAmount);

	UpdateItem();

	// Ensures that the Health never exceeds the max amount
	if (PlayerCharacter->Health >= 100.0f)
	{
		PlayerCharacter->Health = 100.0f;
	}

	ShouldDisablePurchaseButton(TraderAIPTR->HealthPickupAmount, PlayerCharacter->Health);
}