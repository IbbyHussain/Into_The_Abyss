
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_MeleeAIController.generated.h"

UENUM(Blueprintable)
enum class EAIStates : uint8
{
	HOLDING,
	ATTACKING,
	RECOVERING
};


UCLASS()
class MYPROJECT_API AC_MeleeAIController : public AAIController
{
	GENERATED_BODY()

private:
	AC_MeleeAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackBoard;

	class AC_MeleeAI* MeleeAI;

	class AC_SummonerAI* SummonerAI;

protected:

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUM")
	EAIStates AIStatesController;

	virtual void BeginPlay() override;

	void OnPossess(APawn* const CPawn) override;

	class UBlackboardComponent* GetBlackBoard() const;

	// The target the AI will focus on (rotate to face)
	AActor* CurrentTarget;

	void PawnBasicAttack();

	// changes enum state
	UFUNCTION(BlueprintCallable)
	void AIAttack();

	// AI Perception

	// Override this function 
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	bool bInSpecialAttack;

	// Special Attacks

	void DisableSpecialAttack();

	void EnableSavageSpecialAttack();

	void EnableSummonerSpecialAttack();

	FTimerHandle SpecialAttackHandle;

	bool bDoOnce;

	virtual void Tick(float DeltaTime) override;

	class AC_SavageAI* SavageAI;
};
