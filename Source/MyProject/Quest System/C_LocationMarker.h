
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_LocationMarker.generated.h"

UCLASS()
class MYPROJECT_API AC_LocationMarker : public AActor
{
	GENERATED_BODY()

public:	

	AC_LocationMarker();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FText* LocationName;

	UPROPERTY(EditDefaultsOnly, Category = "Location Marker")
	class USphereComponent* CollisonComp;

	// The quest that needs this location marker to complete an objective
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Location Marker")
	class AC_BaseQuest* Quest;

};
