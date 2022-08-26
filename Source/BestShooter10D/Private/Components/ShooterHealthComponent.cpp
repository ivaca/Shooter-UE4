// Best Shooter Ever


#include "Components/ShooterHealthComponent.h"

#include "Dev/FireDamageType.h"
#include "Dev/IceDamageType.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UShooterHealthComponent::UShooterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


bool UShooterHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	SetHealth(HealthAmount);

	return true;
}

bool UShooterHealthComponent::IsHealthFull() const
{
	return Health == MaxHealth;
}

void UShooterHealthComponent::SetHealth(float HealthAmount)
{
	if (HealthAmount <= 0) return;
	Health = FMath::Clamp(HealthAmount + Health, Health, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void UShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth> 0);
	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShooterHealthComponent::OnTakeAnyDamage);
	}
}


void UShooterHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
                                              AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	if (IsDead())
	{
		OnDeath.Broadcast();
		UE_LOG(LogHealthComponent, Display, TEXT("DEAD"));
	}
}
