
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_PickupWidget.generated.h"

class UImage;
class UTexture2D;

UCLASS()
class MYPROJECT_API UC_PickupWidget : public UUserWidget
{
	GENERATED_BODY()

	UC_PickupWidget(const FObjectInitializer& ObjectInitializer);

public:
	void DisplayHealth();

	void DisplayStamina();

	void DisplayMana();

	// Used for when player takes damage rather than pickup
	void DisplayDamage();

	void FadeOut();

	void FadeIn();

private:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Pickup Widget", meta = (BindWidget))
	UImage* PickupImage;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup Widget")
	TArray<UTexture2D*> PickupImageArray;

	void SetPickupImage(UTexture2D* Image);

	//Widget Animation
	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* FadeInAnimation;

	UWidgetAnimation* FadeOutAnimation;

};
