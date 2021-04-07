// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsVideoWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"

void UC_SettingsVideoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Reference to player HUD
	HUD = Cast<AC_PlayerHUD2>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	BackButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::BackButtonClicked);

	// Resolutuion Button bindings 
	SDButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::SDButtonClicked);
	HDButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::HDButtonClicked);
	FHDButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::FHDButtonClicked);
	QHDButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::QHDButtonClicked);

	// AA Button Bindings
	LowButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::LowButtonClicked);
	MediumButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::MediumButtonClicked);
	HighButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::HighButtonClicked);
	EpicButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::EpicButtonClicked);
	
	// Shadow Quality Button Bindings
	SQLowButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::SQLowButtonClicked);
	SQMediumButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::SQMediumButtonClicked);
	SQHighButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::SQHighButtonClicked);
	SQEpicButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::SQEpicButtonClicked);

	// Texture Quality Button Bindings
	TQLowButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::TQLowButtonClicked);
	TQMediumButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::TQMediumButtonClicked);
	TQHighButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::TQHighButtonClicked);
	TQEpicButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::TQEpicButtonClicked);

	// Bloom Quality Button Bindings
	MBLowButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::MBLowButtonClicked);
	MBMediumButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::MBMediumButtonClicked);
	MBHighButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::MBHighButtonClicked);
	MBEpicButton->OnClicked.AddDynamic(this, &UC_SettingsVideoWidget::MBEpicButtonClicked);
}

void UC_SettingsVideoWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}

// Resolution Settings

void UC_SettingsVideoWidget::SDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 720x480"), true);
}

void UC_SettingsVideoWidget::HDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 1280x720"), true);
}

void UC_SettingsVideoWidget::FHDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 1920x1080"), true);
}

void UC_SettingsVideoWidget::QHDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 2560x1440"), true);
}

// AA settings

void UC_SettingsVideoWidget::LowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 0"), true);
}

void UC_SettingsVideoWidget::MediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 2"), true);
}

void UC_SettingsVideoWidget::HighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 4"), true);
}

void UC_SettingsVideoWidget::EpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 6"), true);
}

// SQ Settings

void UC_SettingsVideoWidget::SQLowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 0"), true);
}

void UC_SettingsVideoWidget::SQMediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 1"), true);
}

void UC_SettingsVideoWidget::SQHighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 2"), true);
}

void UC_SettingsVideoWidget::SQEpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 3"), true);
}

// TQ Settings

void UC_SettingsVideoWidget::TQLowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 0"), true);
}

void UC_SettingsVideoWidget::TQMediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 1"), true);
}

void UC_SettingsVideoWidget::TQHighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 2"), true);
}

void UC_SettingsVideoWidget::TQEpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 3"), true);
}

// Bloom Settings

void UC_SettingsVideoWidget::MBLowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 0"), true);
}

void UC_SettingsVideoWidget::MBMediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 1"), true);
}

void UC_SettingsVideoWidget::MBHighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 3"), true);
}

void UC_SettingsVideoWidget::MBEpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 4"), true);
}
