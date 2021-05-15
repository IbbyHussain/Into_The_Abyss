
#include "C_AITalkWindow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyProject/C_PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UC_AITalkWindow::NativeConstruct()
{
	Super::NativeConstruct();

	AISpeechArrayIndex = 1;

	NextButton->OnClicked.AddDynamic(this, &UC_AITalkWindow::OnClickedNextButton);

	for (auto x : AISpeechArray)
	{
		UE_LOG(LogTemp, Log, TEXT("There are: %d items in the AISpeechArray"), AISpeechArray.Num());
	}

	AISpeech->SetText(AISpeechArray[0]);
}

void UC_AITalkWindow::OnClickedNextButton()
{
	if(!bFinished)
	{
		AISpeech->SetText(AISpeechArray[AISpeechArrayIndex]);

		if (AISpeechArrayIndex >= AISpeechArray.Num() - 1)
		{
			AISpeechArrayIndex = 0;

			NextButtonText->SetText(FText::FromString("Close"));
			bFinished = true;
			//AISpeech->SetText(FText::FromString("Dialogue is finished "));

		}

		else
		{
			AISpeechArrayIndex++;
		}
	}

	else
	{
		AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

		if (bClose)
		{
			UE_LOG(LogTemp, Error, TEXT("Start fade out")); // for final message
			PlayerCharacter->EndGame();
		}

		RemoveFromParent();

		APlayerController* PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;

		PlayerCharacter->BroadcastCanTrade();
	}
}