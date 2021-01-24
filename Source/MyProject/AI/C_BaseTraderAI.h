
#pragma once
#include "CoreMinimal.h"
#include "MyProject/AI/C_BaseAI.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_BaseTraderAI.generated.h"

UCLASS()
class MYPROJECT_API AC_BaseTraderAI : public AC_BaseAI, public IC_InteractInterface
{
	GENERATED_BODY()

public:
	AC_BaseTraderAI();

	virtual void BeginPlay() override;

	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;

	// DisplayKeyhint function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisplayKeyHint();

	// Implementation of the DisplayKeyHint function
	virtual void DisplayKeyHint_Implementation() override;

	// RemoveKeyhint function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveKeyHint();

	// Implementation of the RemoveKeyHint function
	virtual void RemoveKeyHint_Implementation() override;

	UFUNCTION()
	void StopInteract(int a);

	//The actor that will give the viewpoint of the camera 
	UPROPERTY(EditInstanceOnly, Category = "Camera")
	AActor* CameraViewPoint;

	FTimerHandle PlayerMeshVisibilityHandle;

	void MakePlayerMeshVisible();

	// Inventory

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 HealthPickupAmount;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 StaminaPickupAmount;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 ManaPickupAmount;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 SteelBoltPickupAmount;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 CopperBoltPickupAmount;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 CrystalBoltPickupAmount;

	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 FlareBoltPickupAmount;

	// The trade window that will be displayed when the player interacts with this AI
	UPROPERTY(EditInstanceOnly, Category = "Trading")
	TSubclassOf<class UC_AITradeWindow> AITradeWidgetClass;

private:
};
