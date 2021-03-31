// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_WeaponWheel.generated.h"

class AC_PlayerCharacter;
class UCanvasPanel;
class UButton;
class UHorizontalBox;
class UImage;


UENUM()
enum class ESelectedOption: uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

UCLASS()
class MYPROJECT_API UC_WeaponWheel : public UUserWidget
{
	GENERATED_BODY()
public:

	UC_WeaponWheel(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "enum")
	ESelectedOption SelectedOption;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UBackgroundBlur* BluredBackground;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* SelectionBox;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* BasicOverlay;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* Top;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Line;

	//The buttons

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OverlayTL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OverlayTR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OverlayBL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OverlayBR;

	// Button clicked functions
	UFUNCTION()
	void OverlayTLClicked();

	UFUNCTION()
	void OverlayTRClicked();

	UFUNCTION()
	void OverlayBLClicked();

	UFUNCTION()
	void OverlayBRClicked();

	//Image for the overlays

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* TL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* TR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* BR;

	//Item Text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTItemName;

	FString ItemName;

	//Texture Changing

	UPROPERTY(EditAnywhere)
	UTexture2D* TRDefault;

	UPROPERTY(EditAnywhere)
	UTexture2D* TRHovered;

	UPROPERTY(EditAnywhere)
	UTexture2D* TLDefault;

	UPROPERTY(EditAnywhere)
	UTexture2D* TLHovered;

	UPROPERTY(EditAnywhere)
	UTexture2D* BRDefault;

	UPROPERTY(EditAnywhere)
	UTexture2D* BRHovered;

	UPROPERTY(EditAnywhere)
	UTexture2D* BLDefault;

	UPROPERTY(EditAnywhere)
	UTexture2D* BLHovered;

	void UpdateTextures();

	// Unlocking Option Slots
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnLockedSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnlockedCrossBow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnlockedMagic;

	//Visibility of this widget class 

	void PlayFadeInAnimation();

	void PlayFadeOutAnimation();

	//Widget Animation

	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	TMap<FName, UWidgetAnimation*> AnimationsMap;

	UWidgetAnimation* FadeInAnimation;

	UWidgetAnimation* FadeOutAnimation;

private:
	AC_PlayerCharacter* Player;

	APlayerController* PlayerController;

	class AC_PlayerHUD2* HUD;

	void RemoveWeaponWheelEffects();

	void ResetGlobalTimeDialation();

	FTimerHandle GlobalTimeDialationHandle;

	void OverlayClickedSettings();

	UFUNCTION()
	void DisableCurrentCombatState();
};
