
#include "C_ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Components/Border.h"
#include "MyProject/C_MainGameInstance.h"
#include "Math/Color.h"
//#include "MyProject/AI/C_BaseTraderAI.h"

UC_ItemWidget::UC_ItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//NumberOfItems = TEXT("");
}

void UC_ItemWidget::NativeConstruct()
{
	GameInstance = Cast<UC_MainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Super::NativeConstruct();

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	TXTPurchase->SetText(FText::FromString("Purchase"));

	ItemImage->SetBrushFromTexture(ItemTexture);

	BackgroundBorder->SetBrushFromTexture(DefaultBackgroundTexture);

	PurchaseButton->SetClickMethod(EButtonClickMethod::DownAndUp);

	UnTintItemImage();
}

void UC_ItemWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	bool x = bIsHoveringBorder();

	if(x)
	{
		//UE_LOG(LogTemp, Log, TEXT("T"));
		ShowHighlight();
	}

	else
	{
		//UE_LOG(LogTemp, Log, TEXT("F"));
		HideHighlight();
	}
}


void UC_ItemWidget::Purchase(int32& Quantity, int32 ItemPrice)
{
	PlayerCharacter->NumberOfSouls -= ItemPrice;
	PlayerCharacter->SaveNumberOfSouls();

	AC_PlayerHUD2* HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	HUD->UpdateCurrency();

	Quantity--;
}

// issues when num of souls is less than price
void UC_ItemWidget::ShouldDisablePurchaseButton(int32& ItemQuantity, float& PlayerStat)
{
	if(PlayerCharacter->NumberOfSouls < 5 || ItemQuantity == 0 || PlayerStat >= 100.0f)
	{
		PurchaseButton->SetIsEnabled(false);
		TintItemImage();
	}
}

// Disables the purchase button if these conditions are met
void UC_ItemWidget::ShouldDisablePurchaseButtonBolts(int32& ItemQuantity, int32& CurrentNumberOfBolts, int32 MaxAmountOfBolts, int32 ItemPrice)
{
	if(PlayerCharacter->NumberOfSouls < ItemPrice || ItemQuantity == 0 || CurrentNumberOfBolts >= MaxAmountOfBolts)
	{
		PurchaseButton->SetIsEnabled(false);
		TintItemImage();
	}
}

void UC_ItemWidget::AttributePurchase(float& Attribute, float Amount, int32& ItemQuantity)
{
	if (PlayerCharacter->NumberOfSouls >= 5)
	{
		Purchase(ItemQuantity, 5);

		Attribute += Amount;
	}
}

void UC_ItemWidget::ShowHighlight()
{
	BackgroundBorder->SetBrushFromTexture(HighlightBackgroundTexture);
}

void UC_ItemWidget::HideHighlight()
{
	BackgroundBorder->SetBrushFromTexture(DefaultBackgroundTexture);
}

bool UC_ItemWidget::bIsHoveringBorder()
{
	bool bISHovered;
	BackgroundBorder->IsHovered() ? bISHovered = true : bISHovered = false ;

	return bISHovered;
}

void UC_ItemWidget::TintItemImage()
{
	FSlateColor DarkGrey = FLinearColor(0.15625f, 0.15625f, 0.15625f, 1.0f);
	ItemImage->SetBrushTintColor(DarkGrey);
}

void UC_ItemWidget::UnTintItemImage()
{
	FSlateColor White = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	ItemImage->SetBrushTintColor(White);
}