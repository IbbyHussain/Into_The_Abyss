
#include "C_AITradeWindow.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/UI/Trading/C_ItemWidget.h"
#include "TimerManager.h"


UC_AITradeWindow::UC_AITradeWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UC_AITradeWindow::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->SetClickMethod(EButtonClickMethod::DownAndUp);
	CloseButton->OnClicked.AddDynamic(this, &UC_AITradeWindow::CloseWidget);

	// Skip frame before validating pointers as the TraderAI pointer is set after the widget is constructed. Frame skip
	FTimerHandle FrameHandle;
	GetWorld()->GetTimerManager().SetTimer(FrameHandle, this, &UC_AITradeWindow::ValidateTraderAI, 0.01f, false);
}

void UC_AITradeWindow::ValidateTraderAI()
{
	// Validate the ptrs
	Item1->TraderAIPTR = TraderAI;
	Item2->TraderAIPTR = TraderAI;
	Item3->TraderAIPTR = TraderAI;
}

void UC_AITradeWindow::CloseWidget()
{
	AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerCharacter->BroadcastCanTrade();
}


