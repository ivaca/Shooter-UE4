// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "ShooterProjectile.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterLauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BESTSHOOTER10D_API AShooterLauncherWeapon : public AShooterBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<AShooterProjectile> ProjectileClass;


	virtual void MakeShot() override;
};
