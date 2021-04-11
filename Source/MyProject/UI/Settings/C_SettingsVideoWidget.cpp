// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SettingsVideoWidget.h"
#include "Components/Button.h"
#include "MyProject/UI/C_PlayerHUD2.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Misc/C_BaseSaveGame.h"

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

	LoadVideoOption();
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
	//SaveVideoOption(EVideoOption::OPTION1, 0);
}

void UC_SettingsVideoWidget::HDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 1280x720"), true);
	//SaveVideoOption(EVideoOption::OPTION2, 0);
}

void UC_SettingsVideoWidget::FHDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 1920x1080"), true);
	//SaveVideoOption(EVideoOption::OPTION3, 0);
}

void UC_SettingsVideoWidget::QHDButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.setres 2560x1440"), true);
	//SaveVideoOption(EVideoOption::OPTION4, 0);
}

// AA settings

void UC_SettingsVideoWidget::LowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 0"), true);
	SaveVideoOption(EVideoOption::OPTION1, 1);
}

void UC_SettingsVideoWidget::MediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 2"), true);
	SaveVideoOption(EVideoOption::OPTION2, 1);
}

void UC_SettingsVideoWidget::HighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 4"), true);
	SaveVideoOption(EVideoOption::OPTION3, 1);
}

void UC_SettingsVideoWidget::EpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 6"), true);
	SaveVideoOption(EVideoOption::OPTION4, 1);
}

// SQ Settings

void UC_SettingsVideoWidget::SQLowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 0"), true);
	SaveVideoOption(EVideoOption::OPTION1, 2);
}

void UC_SettingsVideoWidget::SQMediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 1"), true);
	SaveVideoOption(EVideoOption::OPTION2, 2);
}

void UC_SettingsVideoWidget::SQHighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 2"), true);
	SaveVideoOption(EVideoOption::OPTION3, 2);
}

void UC_SettingsVideoWidget::SQEpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.ShadowQuality 3"), true);
	SaveVideoOption(EVideoOption::OPTION4, 2);
}

// TQ Settings

void UC_SettingsVideoWidget::TQLowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 0"), true);
	SaveVideoOption(EVideoOption::OPTION1, 3);
}

void UC_SettingsVideoWidget::TQMediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 1"), true);
	SaveVideoOption(EVideoOption::OPTION2, 3);
}

void UC_SettingsVideoWidget::TQHighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 2"), true);
	SaveVideoOption(EVideoOption::OPTION3, 3);
}

void UC_SettingsVideoWidget::TQEpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("sg.TextureQuality 3"), true);
	SaveVideoOption(EVideoOption::OPTION4, 3);
}

// Bloom Settings

void UC_SettingsVideoWidget::MBLowButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 0"), true);
	SaveVideoOption(EVideoOption::OPTION1, 4);
}

void UC_SettingsVideoWidget::MBMediumButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 1"), true);
	SaveVideoOption(EVideoOption::OPTION2, 4);
}

void UC_SettingsVideoWidget::MBHighButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 3"), true);
	SaveVideoOption(EVideoOption::OPTION3, 4);
}

void UC_SettingsVideoWidget::MBEpicButtonClicked()
{
	PlayerController->ConsoleCommand(FString("r.BloomQuality 4"), true);
	SaveVideoOption(EVideoOption::OPTION4, 4);
}

// Saving

void UC_SettingsVideoWidget::SaveVideoOption(TEnumAsByte<EVideoOption> Option, int32 Index)
{
	if (UC_BaseSaveGame* SaveGameInstance = Cast<UC_BaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UC_BaseSaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->VideoOptionArray[Index] = SaveGameInstance->VideoOption = Option;

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Video"), 0))
		{
			UE_LOG(LogTemp, Log, TEXT("Save Succeeded (Video)"));
		}
	}
}

void UC_SettingsVideoWidget::LoadVideoOption()
{
	if (UC_BaseSaveGame* LoadedGame = Cast<UC_BaseSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Video"), 0)))
	{
		CheckForVideoOption(LoadedGame, 4);
		CheckForVideoOption(LoadedGame, 3);
		CheckForVideoOption(LoadedGame, 2);
		CheckForVideoOption(LoadedGame, 1);
		//CheckForVideoOption(LoadedGame, 0);
	}
}

void UC_SettingsVideoWidget::CheckForVideoOption(UC_BaseSaveGame* SaveGame, int32 Index)
{
	switch (Index)
	{
	case 0:
		switch (SaveGame->VideoOption)
		{
		case EVideoOption::OPTION1:
			PlayerController->ConsoleCommand(FString("r.setres 720x480"), true);
			break;

		case EVideoOption::OPTION2:
			PlayerController->ConsoleCommand(FString("r.setres 1280x720"), true);
			break;

		case EVideoOption::OPTION3:
			PlayerController->ConsoleCommand(FString("r.setres 1920x1080"), true);
			break;

		case EVideoOption::OPTION4:
			PlayerController->ConsoleCommand(FString("r.setres 2560x1440"), true);
			break;
		}
		break;

	case 1:
		switch (SaveGame->VideoOption)
		{
		case EVideoOption::OPTION1:
			PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 0"), true);
			break;

		case EVideoOption::OPTION2:
			PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 2"), true);
			break;

		case EVideoOption::OPTION3:
			PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 4"), true);
			break;

		case EVideoOption::OPTION4:
			PlayerController->ConsoleCommand(FString("r.PostProcessAAQuality 6"), true);
			break;
		}
		break;

	case 2:
		switch (SaveGame->VideoOption)
		{
		case EVideoOption::OPTION1:
			PlayerController->ConsoleCommand(FString("sg.ShadowQuality 0"), true);
			break;

		case EVideoOption::OPTION2:
			PlayerController->ConsoleCommand(FString("sg.ShadowQuality 1"), true);
			break;

		case EVideoOption::OPTION3:
			PlayerController->ConsoleCommand(FString("sg.ShadowQuality 2"), true);

		case EVideoOption::OPTION4:
			PlayerController->ConsoleCommand(FString("sg.ShadowQuality 3"), true);
			break;
		}
		break;

	case 3:
		switch (SaveGame->VideoOption)
		{
		case EVideoOption::OPTION1:
			PlayerController->ConsoleCommand(FString("sg.TextureQuality 0"), true);
			break;

		case EVideoOption::OPTION2:
			PlayerController->ConsoleCommand(FString("sg.TextureQuality 1"), true);
			break;

		case EVideoOption::OPTION3:
			PlayerController->ConsoleCommand(FString("sg.TextureQuality 2"), true);

		case EVideoOption::OPTION4:
			PlayerController->ConsoleCommand(FString("sg.TextureQuality 3"), true);
			break;
		}
		break;

	case 4:
		switch (SaveGame->VideoOption)
		{
		case EVideoOption::OPTION1:
			PlayerController->ConsoleCommand(FString("r.BloomQuality 0"), true);
			break;

		case EVideoOption::OPTION2:
			PlayerController->ConsoleCommand(FString("r.BloomQuality 1"), true);
			break;

		case EVideoOption::OPTION3:
			PlayerController->ConsoleCommand(FString("r.BloomQuality 3"), true);
			break;

		case EVideoOption::OPTION4:
			PlayerController->ConsoleCommand(FString("r.BloomQuality 4"), true);
			break;
		}
		break;
	}
}