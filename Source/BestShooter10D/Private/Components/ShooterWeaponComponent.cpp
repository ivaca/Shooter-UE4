// Best Shooter Ever


#include "Components/ShooterWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/ShooterBaseWeapon.h"


UShooterWeaponComponent::UShooterWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UShooterWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
}


void UShooterWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())return;


	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<AShooterBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void UShooterWeaponComponent::Fire()
{
	if (!CurrentWeapon)return;
	CurrentWeapon->Fire();
}
