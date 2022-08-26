// Best Shooter Ever


#include "Pickups/ShooterHealthPickup.h"

#include "ShooterUtils.h"
#include "Components/ShooterHealthComponent.h"

bool AShooterHealthPickup::GivePickUpTo(APawn* PlayerPawn)
{
	UE_LOG(LogTemp, Error, TEXT("Ammo was picked"));
	const auto HealthComponent = ShooterUtils::GetPlayerComponent<UShooterHealthComponent>(PlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	HealthComponent->TryToAddHealth(HealthAmount);
	return  true;
}
