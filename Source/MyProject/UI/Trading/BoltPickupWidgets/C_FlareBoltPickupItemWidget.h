// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/UI/Trading/C_ItemWidget.h"
#include "C_FlareBoltPickupItemWidget.generated.h"

UCLASS()
class MYPROJECT_API UC_FlareBoltPickupItemWidget : public UC_ItemWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void ConstructChecks();

	void UpdateItem();

	UFUNCTION()
	void PurchaseFlareBolt();
	
};
