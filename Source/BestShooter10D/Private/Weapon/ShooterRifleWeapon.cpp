// Best Shooter Ever


#include "Weapon/ShooterRifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

void AShooterRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);


	if (HitResult.bBlockingHit)

	{
		auto HitChar = Cast<ACharacter>(HitResult.GetActor());
		if (HitChar)
			HitChar->TakeDamage(HitDamage, FDamageEvent{}, GetPlayerController(), this);

		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Green, false, 3.0f, 0,
		              1.5f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Blue, false, 5.0f);
	}
	DecreaseAmmo();
}


void AShooterRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AShooterRifleWeapon::MakeShot, TimerRate, true);
	MakeShot();
}

void AShooterRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

bool AShooterRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AShooterRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
