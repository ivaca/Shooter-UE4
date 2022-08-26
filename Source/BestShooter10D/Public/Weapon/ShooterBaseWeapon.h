// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterCoreTypes.h"
#include "ShooterBaseWeapon.generated.h"


UCLASS()
class BESTSHOOTER10D_API AShooterBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AShooterBaseWeapon();


	FOnClipEmptySignature OnClipEmpty;
	void ChangeClip();
	bool CanReload() const;
	virtual void StartFire();
	virtual void StopFire();

	FWeaponUIData GetUIData() const { return UIData; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount); 
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	bool IsAmmoFull() const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName MuzzleSocketName = "MuzzleFlashSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FAmmoData DefaultAmmo{30, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float HitDamage = 25.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FWeaponUIData UIData;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	virtual void MakeShot();

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();

	void LogAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	
private:
	FAmmoData CurrentAmmo;
};
