// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "C_MiniMap.generated.h"

class UC_POIComponent;
class UC_PointOfIntrest;

UCLASS()
class MYPROJECT_API UC_MiniMap : public UUserWidget
{
	GENERATED_BODY()

	UC_MiniMap(const FObjectInitializer& ObjectInitializer);
public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	//Set the material parameter collection from the editor
	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* Collection;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* MapOverlay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Map;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	float Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	float Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	class UTexture* MapTexture;

	//Player Icon widget
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> PlayerIcon;

	UPROPERTY(BlueprintReadWrite, Category = "Size")
	UOverlaySlot* SlotRef;

	//Point of intrest widget
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> POI;

	//Add point of intrest

	UFUNCTION(BlueprintCallable)
	UC_PointOfIntrest* AddPOI(AActor* Actor);

	float CalculateZoom();

private:

	UMaterialInstanceDynamic* DynamicMaterial;

	UMaterialParameterCollectionInstance* Instance;

	class UC_PlayerIcon* PlayerIconWidget;

	UC_PointOfIntrest* POIWidget;

	UOverlaySlot* MapOverlaySlot;



};
