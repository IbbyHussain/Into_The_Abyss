
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_ItemWidget.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallChildPurchaseButtons);

UCLASS()
class MYPROJECT_API UC_ItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//UPROPERTY(BlueprintAssignable, Category = "Widget")
	//FCallChildPurchaseButtons CallChildPurchaseButtons;

	UC_ItemWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UVerticalBox* VertBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UButton* PurchaseButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UTextBlock* TXTPurchase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UTextBlock* TXTItemQuantity;

	// Widget Highlight

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	class UBorder* BackgroundBorder;

	UFUNCTION(BlueprintCallable)
	bool bIsHoveringBorder();

	void ShowHighlight();

	void HideHighlight();

	UPROPERTY(EditAnywhere, Category = "ItemImage")
	UTexture2D* ItemTexture;

	FString NumberOfItems;

	class AC_PlayerCharacter* PlayerCharacter;

	void ShouldDisablePurchaseButton(int32& ItemQuantity, float& PlayerStat);

	void ShouldDisablePurchaseButtonBolts(int32& ItemQuantity, int32& CurrentNumberOfBolts, int32 MaxAmountOfBolts, int32 ItemPrice);

	UFUNCTION()
	void Purchase(int32& Quantity, int32 ItemPrice);

	void AttributePurchase(float& Attribute, float Amount, int32& ItemQuantity);

	class UC_MainGameInstance* GameInstance;

	class AC_BaseTraderAI* TraderAIPTR;

	int32 NumberOfBolts;
	int32 MaxNumberOfBolts;
	int32 PriceOfBolt;

	// Will tint the item image when disabled
	void TintItemImage();

	// Will tint the item image when disabled
	void UnTintItemImage();

	//UFUNCTION()
	//void PurchaseButtonClicked();

private:
	UPROPERTY(EditAnywhere, Category = "ItemImage")
	UTexture2D* DefaultBackgroundTexture;

	UPROPERTY(EditAnywhere, Category = "ItemImage")
	UTexture2D* HighlightBackgroundTexture;

};
