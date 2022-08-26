// Best Shooter Ever


#include "Pickups/ShooterAmmoPickup.h"

#include "ShooterUtils.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"

bool AShooterAmmoPickup::GivePickUpTo(APawn* PlayerPawn)
{
	UE_LOG(LogTemp, Error, TEXT("Ammo was picked"));
	const auto HealthComponent = ShooterUtils::GetPlayerComponent<UShooterHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = ShooterUtils::GetPlayerComponent<UShooterWeaponComponent>(PlayerPawn);
	if(!WeaponComponent ) return false;
	return  WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
