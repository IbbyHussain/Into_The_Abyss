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
}

void UC_SettingsVideoWidget::BackButtonClicked()
{
	if (HUD)
	{
		HUD->CreateSettingsWidget();
		RemoveFromParent();
	}
}

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