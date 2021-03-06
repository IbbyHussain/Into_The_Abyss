
#include "C_AITalkWindow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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
	AISpeech->SetText(AISpeechArray[AISpeechArrayIndex]);

	if(AISpeechArrayIndex >= AISpeechArray.Num() - 1)
	{
		AISpeechArrayIndex = 0;

		//AISpeech->SetText(FText::FromString("Dialogue is finished "));
		
	}

	else
	{
		AISpeechArrayIndex++;
	}
}