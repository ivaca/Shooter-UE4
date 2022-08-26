// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Pickups/ShooterBasePickup.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class BESTSHOOTER10D_API AShooterAmmoPickup : public AShooterBasePickup
{
	GENERATED_BODY()
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta = (ClampMin ="1.0", ClampMax="10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	TSubclassOf<AShooterBaseWeapon> WeaponType;
};
