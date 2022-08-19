// Best Shooter Ever


#include "Components/ShooterWeaponComponent.h"

#include "Animations/ShooterEquipFinishedAN.h"
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

	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void UShooterWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}

	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}


void UShooterWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;
	for (auto& WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<AShooterBaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UShooterWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	EquipAnimInProgress = true;
	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	PlayAnimMontage(EquipAnimMontage);
}

void UShooterWeaponComponent::AttachWeaponToSocket(AShooterBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                                   const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

bool UShooterWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress;
}

bool UShooterWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;
}

void UShooterWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UShooterWeaponComponent::InitAnimations()
{
	if (!EquipAnimMontage) return;
	const auto NotifyEvents = EquipAnimMontage->Notifies;
	for (auto& NotifyEvent : NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<UShooterEquipFinishedAN>(NotifyEvent.Notify);
		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &UShooterWeaponComponent::OnEquipedFinished);
			break;
		}
	}
}

void UShooterWeaponComponent::OnEquipedFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;


	EquipAnimInProgress = false;
}

void UShooterWeaponComponent::StartFire()
{
	if (!CanFire())return;
	CurrentWeapon->StartFire();
}

void UShooterWeaponComponent::StopFire()
{
	if (!CurrentWeapon)return;
	CurrentWeapon->StopFire();
}

void UShooterWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
