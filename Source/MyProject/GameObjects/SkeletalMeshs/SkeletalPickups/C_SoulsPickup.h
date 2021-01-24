
#pragma once

#include "CoreMinimal.h"
#include "MyProject/GameObjects/SkeletalMeshs/SkeletalPickups/C_SkeletalPickupBase.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_SoulsPickup.generated.h"

UCLASS()
class MYPROJECT_API AC_SoulsPickup : public AC_SkeletalPickupBase, public IC_InteractInterface
{
	GENERATED_BODY()

	AC_SoulsPickup();

public:
	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;
	
};
