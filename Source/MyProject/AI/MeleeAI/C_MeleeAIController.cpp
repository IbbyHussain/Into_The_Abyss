
#include "C_MeleeAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/AI/MeleeAI/C_MeleeAI.h"
#include "MyProject/AI/MeleeAI/C_MeleeAIBlackBoardKeys.h"
#include "TimerManager.h"

AC_MeleeAIController::AC_MeleeAIController(FObjectInitializer const& ObjectInitializer)
{
	// Used to assign the Behaviour tree in the editor via C++
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/Base_MeleeAI/BT_MeleeAI.BT_MeleeAI'"));

	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}

	// Creates behaviour tree and black board component
	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("MeleeBehaviorTreeComp"));
	BlackBoard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("MeleeBlackBoardComp"));

	// AI Perception, assigning team id
	SetGenericTeamId(FGenericTeamId(5));
}

void AC_MeleeAIController::BeginPlay()
{
	Super::BeginPlay();

	// gets a reference to the class that this controller controls.
	MeleeAI = Cast<AC_MeleeAI>(GetPawn());

	// By default current target will be player character 
	CurrentTarget = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Will run the behaviour tree
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);

	uint8 Holding = (uint8)EAIStates::HOLDING;
	GetBlackBoard()->SetValueAsEnum(BB_MeleeAIKeys::AIStates, Holding);
}

void AC_MeleeAIController::OnPossess(APawn* const CPawn)
{
	Super::OnPossess(CPawn);

	if (BlackBoard)
	{
		BlackBoard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

// Helper function for getting blackboard component
UBlackboardComponent* AC_MeleeAIController::GetBlackBoard() const
{
	return BlackBoard;
}

void AC_MeleeAIController::PawnBasicAttack()
{
	MeleeAI->BasicAttack();
}

void AC_MeleeAIController::AIAttack()
{
	uint8 Attacking = (uint8)EAIStates::ATTACKING;
	GetBlackBoard()->SetValueAsEnum(BB_MeleeAIKeys::AIStates, Attacking);
}

ETeamAttitude::Type AC_MeleeAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	return ETeamAttitude::Neutral;
}
