// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ExitArea.generated.h"

class UC_UW_EKeyHint;
class AC_ExitAreaSpawnLocation;


UCLASS()
class MYPROJECT_API AC_ExitArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ExitArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	class AC_PlayerCharacter* PlayerCharacterRef;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	UC_UW_EKeyHint* EKeyHintWidget;

	TSubclassOf<UC_UW_EKeyHint> WidgetClass;

	UFUNCTION(BlueprintCallable)
	void EKeyPressed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actors")
	FVector ExitAreaActorLocation;


};
