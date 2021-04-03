// Fill out your copyright notice in the Description page of Project Settings.


#include "C_HUDWidget2.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "TimerManager.h"

UC_HUDWidget2::UC_HUDWidget2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WidgetStamina = 1.0f;

	Souls = TEXT("");
}

// BEGIN PLAY
void UC_HUDWidget2::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	FLinearColor HealthBarColor = FColor(255, 0, 0);
	PROHealthBar->SetFillColorAndOpacity(HealthBarColor);
	PROHealthBar->SetPercent(1.0f);

	FLinearColor StaminaBarColor = FColor(0, 255, 0);
	PROStaminaBar->SetFillColorAndOpacity(StaminaBarColor);
	PROStaminaBar->SetPercent(1.0f);

	FLinearColor MagicBarColor = FColor(0, 0, 255);
	PROMagicBar->SetFillColorAndOpacity(MagicBarColor);
	PROMagicBar->SetPercent(1.0f);

	FLinearColor BreathBarColor = FColor(100, 100, 100);
	PROBreathBar->SetFillColorAndOpacity(BreathBarColor);
	PROBreathBar->SetPercent(1.0f);

	// Currency

	// Sets the text block to display the number of souls 
	Souls.AppendInt(PlayerCharacter->NumberOfSouls);
	TXTSoulCounter->SetText(FText::FromString(Souls + " Souls"));

	// Delegate binding
	if(PlayerCharacter)
	{
		PlayerCharacter->UpdatenumberOfSouls.AddDynamic(this, &UC_HUDWidget2::UpdateCurrency);
	}

	//Black fade in
	StoreWidgetAnimation();

	ExitAreaAnimation = GetAnimationByName(TEXT("ExitArea"));
	BeginPlayAnimation = GetAnimationByName(TEXT("BeginPlay"));
	
	BreathBarFadeInAnimation = GetAnimationByName(TEXT("BreathBarFadeIn"));
	BreathBarFadeOutAnimation = GetAnimationByName(TEXT("BreathBarFadeOut"));

	BlackImage->SetRenderOpacity(0.0f);

	PlayerCharacter->DisablePlayerInput();
	FTimerHandle BeginPlayHandle;
	GetWorld()->GetTimerManager().SetTimer(BeginPlayHandle, this, &UC_HUDWidget2::PlayBeginPlayAnimation, 1.0f, false);
}

void UC_HUDWidget2::PlayBeginPlayAnimation()
{
	if (BeginPlayAnimation)
	{
		PlayAnimation(BeginPlayAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
		PlayerCharacter->EnablePlayerInput();
	}
}

//Update Health
void UC_HUDWidget2::UpdateHealth()
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if(Character)
	{
		PROHealthBar->SetPercent(Character->Health / 100.0f);
	}
}

//Update Stamina
void UC_HUDWidget2::UpdateStamina()
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		PROStaminaBar->SetPercent(Character->Stamina / 100.0f);
	}
}

//Update Magic
void UC_HUDWidget2::UpdateMagic()
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		PROMagicBar->SetPercent(Character->Magic / 100.0f);
	}
}

//Update Breath
void UC_HUDWidget2::UpdateBreath()
{
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		PROBreathBar->SetPercent(Character->Breath / 100.0f);
	}
}

// Update number of souls
void UC_HUDWidget2::UpdateCurrency(int num)
{
	if(PlayerCharacter)
	{
		// Emptys the string
		Souls.Empty();

		// Updates the text to the current amount of currency
		Souls.AppendInt(PlayerCharacter->NumberOfSouls);
		TXTSoulCounter->SetText(FText::FromString(Souls + " Souls"));
	}
}

void UC_HUDWidget2::PlayExitAreaAnimation()
{
	PlayAnimation(ExitAreaAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UC_HUDWidget2::BreathBarVisible()
{
	PROBreathBar->SetVisibility(ESlateVisibility::Visible);
}

void UC_HUDWidget2::BreathBarInVisible()
{
	PROBreathBar->SetVisibility(ESlateVisibility::Hidden);
}

void UC_HUDWidget2::PlayBreathBarFadeInAnimation()
{
	PlayAnimation(BreathBarFadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UC_HUDWidget2::PlayBreathBarFadeOutAnimation()
{
	PlayAnimation(BreathBarFadeOutAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

//Stores Widget Animation
void UC_HUDWidget2::StoreWidgetAnimation()
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

UWidgetAnimation* UC_HUDWidget2::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);

	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}

	return nullptr;
}