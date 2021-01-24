#include "C_HealthComponent.h"
#include "MyProject/AI/C_BaseAI.h"

UC_HealthComponent::UC_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Health = 1.0f;
}


void UC_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if(MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UC_HealthComponent::HandleTakeAnyDamage);
	}
}

void UC_HealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, 1.0f);

	UE_LOG(LogTemp, Log, TEXT("Health is: %s for %s"), *FString::SanitizeFloat(Health), *GetOwner()->GetName());

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}


void UC_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
