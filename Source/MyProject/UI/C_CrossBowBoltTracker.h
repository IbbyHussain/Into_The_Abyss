// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_CrossBowBoltTracker.generated.h"

UCLASS()
class MYPROJECT_API UC_CrossBowBoltTracker : public UUserWidget
{
	GENERATED_BODY()

		UC_CrossBowBoltTracker(const FObjectInitializer& ObjectInitializer);

private:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (BindWidget))
	class UTextBlock* CrossbowBoltTracker;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CrossbowBoltIcon;

	//Updates the number of bolts
	void UpdateNumberOfBolts(int32 NumOfBolts);
};
