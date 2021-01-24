
#include "C_BaseTraderAI.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/C_AITradeWindow.h"


AC_BaseTraderAI::AC_BaseTraderAI()
{
	TypeOfAI = ETypeOfAI::TRADER;

	bCanRagdoll = false;
}

void AC_BaseTraderAI::BeginPlay()
{
	Super::BeginPlay();

	bCanRagdoll = false;

	// Binds delegate
	PlayerCharacter->CanTrade.AddDynamic(this, &AC_BaseTraderAI::StopInteract);
}

// when interact with the AI trader
void AC_BaseTraderAI::Interact_Implementation()
{
	if (OverlappingLeverBoxCollision() && bCanTalkAI)
	{
		APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

		// hides the AI health bar
		PlayerCharacter->bIsTrading = true;

		PlayerCharacter->StopSprint();

		// Will open the Trading widget.
		HUD->CreateTradingWindow(AITradeWidgetClass);

		// Validates pointer in trade window widget, this pointer is used to allow the widget to display the number of items from this class
		HUD->AITradeWidget->TraderAI = this;


		if (HUD->AITradeWidget->TraderAI)
		{
			UE_LOG(LogTemp, Log, TEXT("AI: Valid AI PTR"));
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

			// Allows the player to use the mouse and sets the mouse to visible
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}

		RemoveKeyHint_Implementation();
		bShowEKeyHint = false;
	}
}

void AC_BaseTraderAI::DisplayKeyHint_Implementation()
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

void AC_BaseTraderAI::RemoveKeyHint_Implementation()
{
	if (bShowEKeyHint)
	{
		PlayerCharacter->bCanInteractWithAI = false;

		if (HUD)
		{
			HUD->MakeEKeyHintInVisible();
		}
	}
}

// Called when the close button is pressed on the trading window widget
void AC_BaseTraderAI::StopInteract(int a)
{
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	PlayerCharacter->bIsTrading = false;

	// Resets camera view
	PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);

	// Allows the player to use the mouse and sets the mouse to visible
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;

	// After camera has panned back to player camera
	GetWorldTimerManager().SetTimer(PlayerMeshVisibilityHandle, this, &AC_BaseTraderAI::MakePlayerMeshVisible, 1.0f, false);

	HUD->DestroyTradingWindow(AITradeWidgetClass);

	HUD->ShowAllElements();

	bShowEKeyHint = true;
	DisplayKeyHint_Implementation();
}

void AC_BaseTraderAI::MakePlayerMeshVisible()
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
