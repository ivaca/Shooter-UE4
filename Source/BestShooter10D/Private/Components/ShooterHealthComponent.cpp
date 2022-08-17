// Best Shooter Ever


#include "Components/ShooterHealthComponent.h"

#include "Dev/FireDamageType.h"
#include "Dev/IceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UShooterHealthComponent::UShooterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UShooterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UShooterHealthComponent::OnTakeAnyDamage);
	}
}


void UShooterHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
                                              AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogHealthComponent, Warning,TEXT("Damage: %f"), Damage);
	if(DamageType)
	{
		if(DamageType->IsA<UFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Warning,TEXT("UFireDamageType"));
		}
		if(DamageType->IsA<UIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Warning,TEXT("UIceDamageType"));
		}
	}
}
