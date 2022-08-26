// Best Shooter Ever


#include "Components/ShooterWeaponComponent.h"

#include "Animations/ShooterEquipFinishedAN.h"
#include "Animations/ShooterReloadFinishedAN.h"
#include "GameFramework/Character.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "Animations/AnimUtils.h"

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
	for (auto& data : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<AShooterBaseWeapon>(data.WeaponClass);
		if (!Weapon) continue;
		Weapon->OnClipEmpty.AddUObject(this, &UShooterWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UShooterWeaponComponent::OnEmptyClip(AShooterBaseWeapon* Weapon)
{
	if(!Weapon) return;
	if(CurrentWeapon == Weapon)
		ChangeClip();
	else
	{
		for (const auto &WeaponIterator : Weapons)
		{
		if (WeaponIterator == Weapon)
		{
			Weapon->ChangeClip();
		}
		}
	}
}

void UShooterWeaponComponent::ChangeClip()
{
	if (!CanReload()) return;
	ReloadAnimInProgress = true;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();

	PlayAnimMontage(CurrentReloadAM);
}

void UShooterWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) return;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	EquipAnimInProgress = true;
	CurrentWeapon = Weapons[WeaponIndex];

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentReloadAM = CurrentWeaponData ? CurrentWeaponData->ReloadAM : nullptr;
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
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UShooterWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UShooterWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UShooterWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;


	ReloadAnimInProgress = false;
}

void UShooterWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void UShooterWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UShooterEquipFinishedAN>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &UShooterWeaponComponent::OnEquipedFinished);
	}
	else
	{
		checkNoEntry();
	}

	for (auto Data : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UShooterReloadFinishedAN>(Data.ReloadAM);
		if (!ReloadFinishedNotify) { checkNoEntry(); }

		ReloadFinishedNotify->OnNotified.AddUObject(this, &UShooterWeaponComponent::OnReloadFinished);
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
	UE_LOG(LogTemp, Error, TEXT("%d"), CanFire());
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

void UShooterWeaponComponent::Reload()
{
	ChangeClip();
}

bool UShooterWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool UShooterWeaponComponent::GetAmmoUIData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

bool UShooterWeaponComponent::TryToAddAmmo(TSubclassOf<AShooterBaseWeapon> WeaponType, int32 ClipsAmount)
{
	for (const auto &Weapon: Weapons)
	{
		if(Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;
}
