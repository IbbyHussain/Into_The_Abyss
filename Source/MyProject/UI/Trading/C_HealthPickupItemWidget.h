
#pragma once

#include "CoreMinimal.h"
#include "MyProject/UI/Trading/C_ItemWidget.h"
#include "C_HealthPickupItemWidget.generated.h"


UCLASS()
class MYPROJECT_API UC_HealthPickupItemWidget : public UC_ItemWidget
{
	GENERATED_BODY()

	UC_HealthPickupItemWidget(const FObjectInitializer& ObjectInitializer);

public:

	virtual void NativeConstruct() override;

	void ConstructChecks();

	void UpdateItem();

	UFUNCTION()
	void PurchaseHealth();
};
