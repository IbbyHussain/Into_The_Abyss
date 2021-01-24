#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UC_InteractInterface : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IC_InteractInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisplayKeyHint();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RemoveKeyHint();
};
