// Best Shooter Ever


#include "UI/ShooerPlayerHUDWidget.h"

#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"

float UShooerPlayerHUDWidget::GetHealthPercent() const
{

	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UShooerPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UShooerPlayerHUDWidget::GetAmmoUIData(FAmmoData& AmmoData) const
{
	auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;

	return WeaponComponent->GetAmmoUIData(AmmoData);
}

bool UShooerPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent) return false;
	
	return !HealthComponent->IsDead();
	
}

bool UShooerPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

UShooterHealthComponent* UShooerPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(UShooterHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UShooterHealthComponent>(Component);
	if (!HealthComponent) return nullptr;
	return HealthComponent;
}

UShooterWeaponComponent* UShooerPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(UShooterWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UShooterWeaponComponent>(Component);
	return WeaponComponent;
}
