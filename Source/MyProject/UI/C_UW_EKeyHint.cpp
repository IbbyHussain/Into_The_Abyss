// Fill out your copyright notice in the Description page of Project Settings.


#include "C_UW_EKeyHint.h"
#include "Styling/SlateColor.h"

UC_UW_EKeyHint::UC_UW_EKeyHint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetVisibility(ESlateVisibility::Hidden);

	KeyWord = TEXT("KeyWord");
}

void UC_UW_EKeyHint::NativeConstruct()
{
	Super::NativeConstruct();

	TXTEKeyHint->SetText(FText::FromString("Press E to " + KeyWord));
	FSlateColor TextColor = (FColor(0, 0, 0));
	TXTEKeyHint->SetColorAndOpacity(TextColor);

	StoreWidgetAnimation();
	FadeInAnimation = GetAnimationByName(TEXT("FadeIn"));
	FadeOutAnimation = GetAnimationByName(TEXT("FadeOut"));
}

void UC_UW_EKeyHint::BecomeVisible()
{
	SetVisibility(ESlateVisibility::Visible);
	if(FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}

void UC_UW_EKeyHint::BecomeInVisible()
{
	if(FadeOutAnimation)
	{
		PlayAnimation(FadeOutAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}

void UC_UW_EKeyHint::InVisible()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UC_UW_EKeyHint::StoreWidgetAnimation()
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

UWidgetAnimation* UC_UW_EKeyHint::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);

	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}
