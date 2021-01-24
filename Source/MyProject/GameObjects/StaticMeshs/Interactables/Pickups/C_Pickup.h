
#pragma once
#include "CoreMinimal.h"
#include "MyProject/GameObjects/StaticMeshs/C_StaticMeshActorPhysics.h"
#include "MyProject/Interfaces/C_InteractInterface.h"
#include "C_Pickup.generated.h"

UCLASS()
class MYPROJECT_API AC_Pickup : public AC_StaticMeshActorPhysics,public IC_InteractInterface
{
	GENERATED_BODY()

	AC_Pickup();

public:

	// Interact function from interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Interact();

	// Implementation of the interact function
	virtual void Interact_Implementation() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "CPP")
	USoundBase* PickupSound;

	// Function called when base classes are interacted with.
	void OnInteract(float Stat, float Amount);

	UParticleSystem* DespawnEffect;

	FName Attachpoint;

	FTimerHandle DespawnHandle;

	void DestroyThis();
};
