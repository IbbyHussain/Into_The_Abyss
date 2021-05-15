
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_AITalkWindow.generated.h"

UCLASS()
class MYPROJECT_API UC_AITalkWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* NextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NextButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AISpeech;

	UFUNCTION()
	void OnClickedNextButton();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Talk")
	TArray<FText> AISpeechArray;

	int32 AISpeechArrayIndex;

	bool bFinished;

	bool bClose;
};
