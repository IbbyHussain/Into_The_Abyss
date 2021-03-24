// Fill out your copyright notice in the Description page of Project Settings.


#include "C_QuestNPC.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_AITradeWindow.h"
#include "MyProject//Quest System/C_BaseQuest.h"
#include "Components/WidgetComponent.h"
#include "MyProject/Quest System/C_AvailableQuest.h"


AC_QuestNPC::AC_QuestNPC()
{
	TypeOfAI = ETypeOfAI::TRADER;

	bCanRagdoll = false;

	FrontQuestWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget1"));
	BackQuestWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget2"));

	FrontQuestWidget->SetupAttachment(GetMesh());
	BackQuestWidget->SetupAttachment(GetMesh());
}

void AC_QuestNPC::BeginPlay()
{
	Super::BeginPlay();

	bCanRagdoll = false;

	// Binds delegate
	PlayerCharacter->CanTrade.AddDynamic(this, &AC_QuestNPC::StopInteract);

	bTakeAbility2Damage = false;

	for (auto x : SpeechArray)
	{
		UE_LOG(LogTemp, Log, TEXT("There are: %d items in the NPCSpeechArray"), SpeechArray.Num());
	}
}

void AC_QuestNPC::InteractFunctionality()
{
	DestroyAvailableQuestWidget();

	GetAttachedActors(AttachedActorsArray, true);

	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	// hides the AI health bar
	PlayerCharacter->bIsTrading = true;

	PlayerCharacter->StopSprint();


	if (QuestREF)
	{
		QuestREF->CheckInteractionObjective(this);
	}

	for (auto i : AttachedActorsArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("There are: %d attached actors"), AttachedActorsArray.Num());

		AC_BaseQuest* Quest = Cast<AC_BaseQuest>(i);

		if (Quest)
		{
			if (!Quest->bIsCompleted)
			{
				if (Quest->bHasBeenAccepted)
				{
					// Will open the turn in quest widget
					HUD->DestroyQuestWidget();
					HUD->CreateQuestTurnInWidget(Quest, this, LevelManager);
				}

				else
				{
					// Will open the Quest widget.
					HUD->CreateQuestWidget(Quest);
				}
			}
		}

	}

	// Hides the HUD
	HUD->HideAllElements();

	// Disables all input
	PlayerCharacter->DisablePlayerInput();

	// Stops player movement and locks camera movement.
	PlayerCharacter->MovementState = EMovementState::NONE;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = true;

	PlayerCharacter->GetMesh()->SetVisibility(false);

	if (PlayerController)
	{
		// Changes camera view to the camera view actor
		PlayerController->SetViewTargetWithBlend(CameraViewPoint, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);

		GetWorldTimerManager().SetTimer(CameraHandle, this, &AC_QuestNPC::EnableUIInput, 1.0f, false);
	}

	RemoveKeyHint_Implementation();
	bShowEKeyHint = false;
}

void AC_QuestNPC::TalkAIFunctionality()
{


	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	// hides the AI health bar
	PlayerCharacter->bIsTrading = true;

	PlayerCharacter->StopSprint();

	if (QuestREF)
	{
		QuestREF->CheckInteractionObjective(this);
	}

	HUD->CreateTalkWindow(SpeechArray);

	// Hides the HUD
	HUD->HideAllElements();

	// Disables all input
	PlayerCharacter->DisablePlayerInput();

	// Stops player movement and locks camera movement.
	PlayerCharacter->MovementState = EMovementState::NONE;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = true;

	PlayerCharacter->GetMesh()->SetVisibility(false);

	if (PlayerController)
	{
		// Changes camera view to the camera view actor
		PlayerController->SetViewTargetWithBlend(CameraViewPoint, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);

		GetWorldTimerManager().SetTimer(CameraHandle, this, &AC_QuestNPC::EnableUIInput, 1.0f, false);
	}

	RemoveKeyHint_Implementation();
	bShowEKeyHint = false;
}

// when interact with the AI trader
void AC_QuestNPC::Interact_Implementation()
{
	if (OverlappingLeverBoxCollision() && bCanTalkAI )
	{
		if(bIsQuestGiver)
		{
			// If the AI has a PreRequisite quest, that quest must be complete before they can be interacted with
			if (QuestREF->PreRequisiteQuest && QuestREF->PreRequisiteQuest->bIsCompleted)
			{
				InteractFunctionality();
			}

			else if (QuestREF->PreRequisiteQuest == NULL)
			{
				InteractFunctionality();
			}
		}

		else
		{
			TalkAIFunctionality();
		}
	}
}

void AC_QuestNPC::EnableUIInput()
{
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	// Allows the player to use the mouse and sets the mouse to visible
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
}

void AC_QuestNPC::DisplayKeyHint_Implementation()
{
	if (bShowEKeyHint)
	{
		PlayerCharacter->bCanInteractWithAI = true;

		if (HUD)
		{
			HUD->SetEKeyHintText("Talk");
			HUD->MakeEKeyHintVisible();
		}
	}
}

void AC_QuestNPC::RemoveKeyHint_Implementation()
{
	if (bShowEKeyHint)
	{
		PlayerCharacter->bCanInteractWithAI = false;


		if (HUD)
		{
			HUD->MakeEKeyHintInVisible();
			UE_LOG(LogTemp, Warning, TEXT("called yfefesfewfefeas"));
		}
	}
}

// Called when the close button is pressed on the trading window widget
void AC_QuestNPC::StopInteract(int a)
{
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	PlayerCharacter->bIsTrading = false;

	// Resets camera view
	PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);

	// Allows the player to use the mouse and sets the mouse to visible
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;

	// After camera has panned back to player camera
	GetWorldTimerManager().SetTimer(PlayerMeshVisibilityHandle, this, &AC_QuestNPC::MakePlayerMeshVisible, 1.0f, false);

	HUD->DestroyQuestWidget();

	HUD->ShowAllElements();

	bShowEKeyHint = true;
	DisplayKeyHint_Implementation();
}

void AC_QuestNPC::MakePlayerMeshVisible()
{
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	PlayerCharacter->GetMesh()->SetVisibility(true);

	// Enables input
	PlayerCharacter->EnablePlayerInput();

	// Allows player to move again.
	PlayerCharacter->MovementState = EMovementState::STANDING;
	PlayerCharacter->UpdateMovement();
	PlayerCharacter->bLockCamera = false;
}

void AC_QuestNPC::DestroyQuestWidgets()
{
	if(bShouldHaveQuestIcon)
	{
		if(FrontQuestWidget && BackQuestWidget)
		{
			FrontQuestWidget->DestroyComponent();
			BackQuestWidget->DestroyComponent();
		}
	}
}