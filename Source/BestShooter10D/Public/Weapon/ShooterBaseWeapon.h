// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterBaseWeapon.generated.h"

UCLASS()
class BESTSHOOTER10D_API AShooterBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AShooterBaseWeapon();

	virtual void Fire();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName = "MuzzleFlashSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector &TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
private:
};
