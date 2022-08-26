// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShooterBasePickup.h"
#include "ShooterHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class BESTSHOOTER10D_API AShooterHealthPickup : public AShooterBasePickup
{
	GENERATED_BODY()

	
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin ="1.0", ClampMax="10.0"))
	int32 HealthAmount = 50.0f;
};

