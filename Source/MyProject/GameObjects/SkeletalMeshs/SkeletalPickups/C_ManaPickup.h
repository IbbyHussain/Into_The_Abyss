#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SkeletalPickupBase.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_ManaPickup.generated.h"

UCLASS()
class MYPROJECT_API AC_ManaPickup : public AC_SkeletalPickupBase, public IC_InteractInterface
{
	GENERATED_BODY()

	AC_ManaPickup();

public:
	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;
};
