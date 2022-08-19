// Best Shooter Ever


#include "Weapon/ShooterLauncherWeapon.h"
#include "Kismet/GameplayStatics.h"

void AShooterLauncherWeapon::StartFire()
{
	MakeShot();
}

void AShooterLauncherWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;

	MakeHit(HitResult, TraceStart, TraceEnd);
 
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	auto Projectile = GetWorld()->SpawnActorDeferred<AShooterProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
}
