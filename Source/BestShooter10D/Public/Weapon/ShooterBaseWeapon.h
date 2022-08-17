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

};
