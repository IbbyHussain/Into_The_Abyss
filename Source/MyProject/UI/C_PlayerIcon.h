// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_PlayerIcon.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_PlayerIcon : public UUserWidget
{
	GENERATED_BODY()

	UC_PlayerIcon(const FObjectInitializer& ObjectInitializer);
public:

	//virtual void NativePreConstruct() override;

	//virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* IconOverlay;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* PlayerIcon;
	
};
