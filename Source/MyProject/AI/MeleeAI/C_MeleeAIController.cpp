
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
#include "MyProject/Components/C_HealthComponent.h"
#include "MyProject/AI/EnglishEnemies/C_SavageAI.h"

AC_MeleeAIController::AC_MeleeAIController(FObjectInitializer const& ObjectInitializer)
{
	// Used to assign the Behaviour tree in the editor via C++
	/*static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/Base_MeleeAI/BT_MeleeAI.BT_MeleeAI'"));

	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}*/

	PrimaryActorTick.bCanEverTick = true;

	// Creates behaviour tree and black board component
	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("MeleeBehaviorTreeComp"));
	BlackBoard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("MeleeBlackBoardComp"));

	bDoOnce = true;

	// AI Perception, assigning team id
	SetGenericTeamId(FGenericTeamId(5));
}

void AC_MeleeAIController::BeginPlay()
{
	Super::BeginPlay();

	// gets a reference to the class that this controller controls.
	MeleeAI = Cast<AC_MeleeAI>(GetPawn());

	SavageAI = Cast<AC_SavageAI>(MeleeAI);

	// By default current target will be player character 
	CurrentTarget = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Will run the behaviour tree
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);

	// Default values for blackboard keys

	uint8 Holding = (uint8)EAIStates::HOLDING;
	GetBlackBoard()->SetValueAsEnum(BB_MeleeAIKeys::AIStates, Holding);
}

void AC_MeleeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Only savage AI can perform melee special attacks
	if (SavageAI && SavageAI->HealthComp->Health <= 0.3 && bDoOnce)
	{
		UE_LOG(LogTemp, Error, TEXT("Special Attack enabled INIT"));
		GetBlackBoard()->SetValueAsBool(BB_MeleeAIKeys::CanUseSpecialAttack, true);
		bDoOnce = false;
	}
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
	/*if(!bInSpecialAttack)
	{
		
	}*/

	uint8 Attacking = (uint8)EAIStates::ATTACKING;
	GetBlackBoard()->SetValueAsEnum(BB_MeleeAIKeys::AIStates, Attacking);
}

void AC_MeleeAIController::DisableSpecialAttack()
{
	GetBlackBoard()->SetValueAsBool(BB_MeleeAIKeys::CanUseSpecialAttack, false);

	UE_LOG(LogTemp, Error, TEXT("Special Attack Disabled"));

	GetWorldTimerManager().SetTimer(SpecialAttackHandle, this, &AC_MeleeAIController::EnableSpecialAttack, 25.0f);
}

void AC_MeleeAIController::EnableSpecialAttack()
{
	if(SavageAI && SavageAI->HealthComp->Health <= 0.3f)
	{
		UE_LOG(LogTemp, Error, TEXT("Special Attack enabled"));
		GetBlackBoard()->SetValueAsBool(BB_MeleeAIKeys::CanUseSpecialAttack, true);
	}
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

