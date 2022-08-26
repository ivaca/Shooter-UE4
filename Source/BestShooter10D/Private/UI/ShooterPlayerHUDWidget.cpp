// Best Shooter Ever


#include "UI/ShooterPlayerHUDWidget.h"

#include "ShooterUtils.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"

float UShooterPlayerHUDWidget::GetHealthPercent() const
{

	const auto HealthComponent = ShooterUtils::GetPlayerComponent<UShooterHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UShooterPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	auto WeaponComponent = ShooterUtils::GetPlayerComponent<UShooterWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UShooterPlayerHUDWidget::GetAmmoUIData(FAmmoData& AmmoData) const
{
	auto WeaponComponent = ShooterUtils::GetPlayerComponent<UShooterWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetAmmoUIData(AmmoData);
}

bool UShooterPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = ShooterUtils::GetPlayerComponent<UShooterHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return false;
	
	return !HealthComponent->IsDead();
	
}

bool UShooterPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

