#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_BaseAIController.generated.h"

UCLASS()
class MYPROJECT_API AC_BaseAIController : public AAIController
{
	GENERATED_BODY()

	AC_BaseAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());


private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackBoard;
protected:

public:
	
	virtual void BeginPlay() override;

	void OnPossess(APawn* const CPawn) override;

	class UBlackboardComponent* GetBlackBoard() const;
};
