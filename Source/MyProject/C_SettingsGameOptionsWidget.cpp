// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsGameOptionsWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

void UC_SettingsGameOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsGameOptionsWidget::BackButtonClicked);

	// View Distance Button Bindings
	NearButton->OnClicked.AddDynamic(this, &UC_SettingsGameOptionsWidget::NearButtonClicked);
	MediumButton->OnClicked.AddDynamic(this, &UC_SettingsGameOptionsWidget::MediumButtonClicked);
	FarButton->OnClicked.AddDynamic(this, &UC_SettingsGameOptionsWidget::FarButtonClicked);
}

void UC_SettingsGameOptionsWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}

// View Distance

void UC_SettingsGameOptionsWidget::NearButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.ViewDistanceScale 0.4"), true);
}

void UC_SettingsGameOptionsWidget::MediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.ViewDistanceScale 0.7"), true);
}

void UC_SettingsGameOptionsWidget::FarButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.ViewDistanceScale 1.0"), true);
}
