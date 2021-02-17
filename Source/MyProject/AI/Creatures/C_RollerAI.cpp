
#include "C_RollerAI.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "MyProject/C_PlayerCharacter.h"
#include "MyProject/Components/C_HealthComponent.h"
#include "DrawDebugHelpers.h"

AC_RollerAI::AC_RollerAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	HealthComp = CreateDefaultSubobject<UC_HealthComponent>(TEXT("Health Comp"));
	HealthComp->OnHealthChanged.AddDynamic(this, &AC_RollerAI::HandleTakeDamage);

	bUseVelocityChange = true;
	MovementForce = 1000.0f;

	RequiredDistanceToTarget = 100.0f;
}

void AC_RollerAI::BeginPlay()
{
	Super::BeginPlay();
	
	// Find inital Move to
	NextPathPoint = GetNextPathPoint();
}

void AC_RollerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	if (DistanceToTarget <= RequiredDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();
	}

	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();

		ForceDirection *= MovementForce;

		MeshComp->AddForce(ForceDirection, NAME_None, bUseVelocityChange);
	}
}

FVector AC_RollerAI::GetNextPathPoint()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerCharacter);

	if (NavPath->PathPoints.Num() > 1)
	{
		return NavPath->PathPoints[1];
	}

	return GetActorLocation();
}

void AC_RollerAI::SelfDestruct()
{
	// Play particle effect and sound
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());

	FCollisionQueryParams CollisionParams;

	TArray<FHitResult> OutHits;

	FVector ActorLocation = GetActorLocation();

	// Creates a sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(150.0f);

	// Debug 
	DrawDebugSphere(GetWorld(), ActorLocation, MyColSphere.GetSphereRadius(), 20, FColor::Green, true);

	// A sweep trace that will hit anything within the sphere
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, ECC_Visibility, MyColSphere, CollisionParams);

	if (bHit)
	{
		for (auto& Hit : OutHits)
		{
			AC_PlayerCharacter* PlayerCharacter = Cast<AC_PlayerCharacter>(Hit.GetActor());

			UE_LOG(LogTemp, Error, TEXT("Roller AI Hit: %s"), *Hit.GetActor()->GetName());

			if (Hit.GetActor() == PlayerCharacter && !bAttackedPlayer)
			{
				bAttackedPlayer = true;
				PlayerCharacter->ApplyDamageToPlayer(5.0f);
			}
		}
	}

	Destroy();
}

void AC_RollerAI::HandleTakeDamage(UC_HealthComponent* HealthCompRef, float Health, float HealthDelta, const class UDamageType* DmgType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Health <= 0.0f)
	{
		SelfDestruct();
	}
	UE_LOG(LogTemp, Error, TEXT("Roller AI Health %s"), *FString::SanitizeFloat(Health));
}