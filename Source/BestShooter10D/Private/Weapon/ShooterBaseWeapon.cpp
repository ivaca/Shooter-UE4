// Best Shooter Ever


#include "Weapon/ShooterBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All,All)

AShooterBaseWeapon::AShooterBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}


void AShooterBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AShooterBaseWeapon::Fire()
{
	
	UE_LOG(LogBaseWeapon, Warning, TEXT("Fire"));
}


