// Best Shooter Ever


#include "Weapon/ShooterBaseWeapon.h"

#include <string>

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

AShooterBaseWeapon::AShooterBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}


bool AShooterBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

	if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if (DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmo.Clips =  DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}
	return true;
}

bool AShooterBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void AShooterBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets cannot be 0 or less"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips cannot be 0 or less"));
	CurrentAmmo = DefaultAmmo;
}

void AShooterBaseWeapon::MakeShot()
{
}


void AShooterBaseWeapon::StartFire()
{
}

void AShooterBaseWeapon::StopFire()
{
}

APlayerController* AShooterBaseWeapon::GetPlayerController() const
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character) return nullptr;

	return Character->GetController<APlayerController>();
}

bool AShooterBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector AShooterBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AShooterBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;

	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AShooterBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
	                                     CollisionQueryParams);
}

void AShooterBaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		return;
	}
	--CurrentAmmo.Bullets;
	LogAmmo();
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

void AShooterBaseWeapon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			return;
		}
		--CurrentAmmo.Clips;
	}
	UE_LOG(LogBaseWeapon, Display, TEXT("Change Clip called"));
}

bool AShooterBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void AShooterBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool AShooterBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && !CurrentAmmo.Clips && IsClipEmpty();
}

bool AShooterBaseWeapon::IsClipEmpty() const
{
	return !CurrentAmmo.Bullets;
}
