// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ShooterCoreTypes.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterWeaponComponent.generated.h"


class AShooterBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BESTSHOOTER10D_API UShooterWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShooterWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetAmmoUIData(FAmmoData& AmmoData) const;
	

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TArray<FWeaponData> WeaponData;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
private:
	void SpawnWeapons();

	void OnEmptyClip();
	void ChangeClip();

	UPROPERTY()
	AShooterBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	UAnimMontage* CurrentReloadAM = nullptr;

	void EquipWeapon(int32 WeaponIndex);
	void AttachWeaponToSocket(AShooterBaseWeapon* BaseWeapon, USceneComponent* SceneComponent, const FName& SocketName);

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	int32 CurrentWeaponIndex = 0;
	UPROPERTY()
	TArray<AShooterBaseWeapon*> Weapons;
	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipedFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
};
