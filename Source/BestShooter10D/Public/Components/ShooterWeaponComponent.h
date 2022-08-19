// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterWeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BESTSHOOTER10D_API UShooterWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShooterWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TArray<TSubclassOf<AShooterBaseWeapon>> WeaponClasses;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
private:
	void SpawnWeapons();

	UPROPERTY()
	AShooterBaseWeapon* CurrentWeapon = nullptr;

	void EquipWeapon(int32 WeaponIndex);
	void AttachWeaponToSocket(AShooterBaseWeapon* BaseWeapon, USceneComponent* SceneComponent, const FName& SocketName);

	bool EquipAnimInProgress = false;
	bool CanFire() const;
	bool CanEquip() const;
	int32 CurrentWeaponIndex = 0;
	UPROPERTY()
	TArray<AShooterBaseWeapon*> Weapons;
	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipedFinished(USkeletalMeshComponent* MeshComponent);
};
