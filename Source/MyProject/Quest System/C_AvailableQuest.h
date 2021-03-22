// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_AvailableQuest.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UC_AvailableQuest : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* QuestIMG;

	UFUNCTION(BlueprintCallable)
	void SetQuestMarkerImage(class AC_BaseQuest* Quest);

	UPROPERTY(EditAnywhere, Category = "Available Quest")
	UTexture2D* PreRequisiteQuestTexture;

	UPROPERTY(EditAnywhere, Category = "Available Quest")
	UTexture2D* DefaultQuestTexture;

	UFUNCTION(BlueprintCallable)
	void CheckQuestMarkerImage(class AC_BaseQuest* Quest);
};
