// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterWeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BESTSHOOTER10D_API UShooterWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShooterWeaponComponent();

	void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<AShooterBaseWeapon> WeaponClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

private:
	void SpawnWeapon();

	UPROPERTY()
	AShooterBaseWeapon* CurrentWeapon = nullptr;
};
