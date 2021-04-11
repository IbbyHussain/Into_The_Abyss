// Fill out your copyright notice in the Description page of Project Settings.


#include "C_WeaponWheel.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/BackgroundBlur.h"
#include "Components/Overlay.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "TimerManager.h"

UC_WeaponWheel::UC_WeaponWheel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Sets the ItemName Texts default Value
	ItemName = TEXT("Item Name");

	SetVisibility(ESlateVisibility::Hidden);
}

void UC_WeaponWheel::NativeConstruct()
{
	Super::NativeConstruct();

	//Reference to Player and Player Controller
	Player = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	TXTItemName->SetText(FText::FromString(ItemName));

	StoreWidgetAnimation();
	FadeInAnimation = GetAnimationByName(TEXT("FadeIn"));
	FadeOutAnimation = GetAnimationByName(TEXT("FadeOut"));

	//Button clicked event bindings
	OverlayTL->OnClicked.AddDynamic(this, &UC_WeaponWheel::OverlayTLClicked);
	OverlayTR->OnClicked.AddDynamic(this, &UC_WeaponWheel::OverlayTRClicked);
	OverlayBL->OnClicked.AddDynamic(this, &UC_WeaponWheel::OverlayBLClicked);
	OverlayBR->OnClicked.AddDynamic(this, &UC_WeaponWheel::OverlayBRClicked);

	// Binds the delegate in the player class which will disbale the button for the current combat state
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		Character->DisableCurrentCombatState.AddDynamic(this, &UC_WeaponWheel::DisableCurrentCombatState);
	}

}

void UC_WeaponWheel::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	TXTItemName->SetText(FText::FromString(ItemName));

	if (OverlayTL->IsHovered())
	{
		SelectedOption = ESelectedOption::TopLeft;
		ItemName = FString("Unarmed");
	}

	else if (OverlayTR->IsHovered())
	{
		SelectedOption = ESelectedOption::TopRight;
		bUnLockedSword ? ItemName = FString("Melee"): ItemName = FString("Locked");
	}

	else if (OverlayBR->IsHovered())
	{
		SelectedOption = ESelectedOption::BottomRight;
		bUnlockedCrossBow ? ItemName = FString("Crossbow"): ItemName = FString("Locked");
	}

	else if (OverlayBL->IsHovered())
	{
		SelectedOption = ESelectedOption::BottomLeft;
		bUnlockedMagic ? ItemName = FString("Magic"): ItemName = FString("Locked");
	}

	UpdateTextures();
}

// Top Left clicked
void UC_WeaponWheel::OverlayTLClicked()
{
	Player->CombatState = ECombatState::UNARMED;
	OverlayClickedSettings();
}

// Top Right clicked  
void UC_WeaponWheel::OverlayTRClicked()
{
	if(bUnLockedSword)
	{
		Player->CombatState = ECombatState::MELEE;
		OverlayClickedSettings();
	}
}

// Bottom Left clicked
void UC_WeaponWheel::OverlayBLClicked()
{
	if(bUnlockedMagic)
	{
		Player->CombatState = ECombatState::MAGIC;
		OverlayClickedSettings();
	}
}

// Bottom Right clicked
void UC_WeaponWheel::OverlayBRClicked()
{
	if(bUnlockedCrossBow)
	{
		Player->CombatState = ECombatState::RANGED;
		OverlayClickedSettings();
	}
}

void UC_WeaponWheel::OverlayClickedSettings()
{
	Player->bShowWeaponWheel = true;
	Player->UpdateCombatState();
	PlayFadeOutAnimation();
	RemoveWeaponWheelEffects();
}
// Removes weapon wheel effects
void UC_WeaponWheel::RemoveWeaponWheelEffects()
{
	GetWorld()->GetTimerManager().SetTimer(GlobalTimeDialationHandle, this, &UC_WeaponWheel::ResetGlobalTimeDialation, 0.1f, false);
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}

void UC_WeaponWheel::ResetGlobalTimeDialation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	GetWorld()->GetTimerManager().ClearTimer(GlobalTimeDialationHandle);
}

void UC_WeaponWheel::UpdateTextures()
{
	// Sets the textures to hovered state if the mouse hovers over them
	if(OverlayBL->bIsEnabled)
	{
		BL->SetBrushFromTexture(SelectedOption == ESelectedOption::BottomLeft ? BLHovered : BLDefault, false);
	}
	
	if (OverlayBR->bIsEnabled)
	{
		BR->SetBrushFromTexture(SelectedOption == ESelectedOption::BottomRight ? BRHovered : BRDefault, false);
	}

	if (OverlayTR->bIsEnabled)
	{
		TR->SetBrushFromTexture(SelectedOption == ESelectedOption::TopRight ? TRHovered : TRDefault, false);
	}

	if (OverlayTL->bIsEnabled)
	{
		TL->SetBrushFromTexture(SelectedOption == ESelectedOption::TopLeft ? TLHovered : TLDefault, false);
	}
}

// Play functions for widget animations

void UC_WeaponWheel::PlayFadeInAnimation()
{
	SetVisibility(ESlateVisibility::Visible);
	if(FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}

void UC_WeaponWheel::PlayFadeOutAnimation()
{
	if (FadeOutAnimation)
	{
		PlayAnimation(FadeOutAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}

// Disables the button for the current combat state
void UC_WeaponWheel::DisableCurrentCombatState()
{
	if(Player->CombatState == ECombatState::UNARMED)
	{
		OverlayTL->SetIsEnabled(false);
		OverlayTR->SetIsEnabled(true);
		OverlayBL->SetIsEnabled(true);
		OverlayBR->SetIsEnabled(true);

		TL->SetBrushFromTexture(TLDisabled);
		TR->SetBrushFromTexture(TRDefault);
		BL->SetBrushFromTexture(BLDefault);
		BR->SetBrushFromTexture(BRDefault);
	}

	else if (Player->CombatState == ECombatState::MELEE)
	{
		OverlayTL->SetIsEnabled(true);
		OverlayTR->SetIsEnabled(false);
		OverlayBL->SetIsEnabled(true);
		OverlayBR->SetIsEnabled(true);

		TR->SetBrushFromTexture(TRDisabled);
		TL->SetBrushFromTexture(TLDefault);
		BL->SetBrushFromTexture(BLDefault);
		BR->SetBrushFromTexture(BRDefault);
	}

	else if (Player->CombatState == ECombatState::MAGIC)
	{
		OverlayTL->SetIsEnabled(true);
		OverlayTR->SetIsEnabled(true);
		OverlayBL->SetIsEnabled(false);
		OverlayBR->SetIsEnabled(true);

		BL->SetBrushFromTexture(BLDisabled);
		TR->SetBrushFromTexture(TRDefault);
		TL->SetBrushFromTexture(TLDefault);
		BR->SetBrushFromTexture(BRDefault);
	}

	else
	{
		OverlayTL->SetIsEnabled(true);
		OverlayTR->SetIsEnabled(true);
		OverlayBL->SetIsEnabled(true);
		OverlayBR->SetIsEnabled(false);

		BR->SetBrushFromTexture(BRDisabled);
		TR->SetBrushFromTexture(TRDefault);
		TL->SetBrushFromTexture(TLDefault);
		BL->SetBrushFromTexture(BLDefault);
	}
}

//Binding widget animation setup

void UC_WeaponWheel::StoreWidgetAnimation()
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

UWidgetAnimation* UC_WeaponWheel::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);

	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}
