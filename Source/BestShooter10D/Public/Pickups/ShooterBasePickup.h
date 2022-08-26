// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "ShooterBasePickup.generated.h"

UCLASS()
class BESTSHOOTER10D_API AShooterBasePickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterBasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingMovementComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float RespawnTime = 5.0f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	
	virtual bool GivePickUpTo(APawn* PlayerPawn);
	void PickupWasTaken();
	void Respawn();
	
};
