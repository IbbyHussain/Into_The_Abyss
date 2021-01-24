
#include "C_PickupWidget.h"
#include "Components/Image.h"

UC_PickupWidget::UC_PickupWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_PickupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreWidgetAnimation();
	FadeInAnimation = GetAnimationByName(TEXT("PickupWidgetFadeIn"));
	FadeOutAnimation = GetAnimationByName(TEXT("PickupWidgetFadeOut"));
}


void UC_PickupWidget::SetPickupImage(UTexture2D* Image)
{
	PickupImage->SetBrushFromTexture(Image); // read access violation
}

// Displays Health Image
void UC_PickupWidget::DisplayHealth()
{
	SetPickupImage(PickupImageArray[0]);
}

// Displays Stamina Image
void UC_PickupWidget::DisplayStamina()
{
	SetPickupImage(PickupImageArray[1]);
}

// Displays Mana Image
void UC_PickupWidget::DisplayMana()
{
	SetPickupImage(PickupImageArray[2]);
}

void UC_PickupWidget::FadeOut()
{
	PlayAnimation(FadeOutAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f); //: Access violation executing location 
}

void UC_PickupWidget::FadeIn()
{
	PlayAnimation(FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

// Widget Animation
void UC_PickupWidget::StoreWidgetAnimation()
{
	AnimationsMap.Empty();

	UProperty* Prop = GetClass()->PropertyLink;

	while (Prop)
	{
		// only evaluate object properties, skip rest
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			// only get back properties that are of type widget animation
			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
				// only get back properties that are of type widget animation
				UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(Obj);
				// if casting worked update map with new animation
				if (WidgetAnimation && WidgetAnimation->MovieScene)
				{
					FName AnimName = WidgetAnimation->MovieScene->GetFName();
					GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, AnimName.ToString());
					AnimationsMap.Add(AnimName, WidgetAnimation);
				}
			}
		}
		Prop = Prop->PropertyLinkNext;
	}
}

UWidgetAnimation* UC_PickupWidget::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);

	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}
