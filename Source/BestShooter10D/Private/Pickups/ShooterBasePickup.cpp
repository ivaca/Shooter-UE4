// Best Shooter Ever


#include "Pickups/ShooterBasePickup.h"

// Sets default values
AShooterBasePickup::AShooterBasePickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(CollisionComponent);


	RotatingMovementComponent= CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
}

// Called when the game starts or when spawned
void AShooterBasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
}

void AShooterBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);\
	if(GivePickUpTo(Pawn))
		PickupWasTaken();
}

bool AShooterBasePickup::GivePickUpTo(APawn* PlayerPawn)
{
	return  false;
}

// Called every frame
void AShooterBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AShooterBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AShooterBasePickup::Respawn, RespawnTime);
}

void AShooterBasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}

