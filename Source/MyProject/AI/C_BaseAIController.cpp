#include "C_BaseAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "MyProject/AI/C_BaseAI.h"

AC_BaseAIController::AC_BaseAIController(FObjectInitializer const& ObjectInitializer)
{
	// Used to assign the Behaviour tree in the editor via C++
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/BaseAI/BT_BaseAI.BT_BaseAI'"));

	if(obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}

	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));

	BlackBoard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
}

void AC_BaseAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);

}

void AC_BaseAIController::OnPossess(APawn* const CPawn)
{
	Super::OnPossess(CPawn);

	if(BlackBoard)
	{
		BlackBoard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* AC_BaseAIController::GetBlackBoard() const
{
	return BlackBoard;
}
