// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon/ShooterBaseWeapon.h"
#include "ShooterBaseCharacter.generated.h"

UCLASS()
class BESTSHOOTER10D_API AShooterBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UShooterHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* HealthTextComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UShooterWeaponComponent* WeaponComponent;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSprintSpeed{900.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool isRunning{false};
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection()const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	FVector2D LandedDamage = FVector2D(10.0f,100.0f);


	
	float InitialSpeed;


	UPROPERTY(EditDefaultsOnly,  Category="Animation")
	UAnimMontage* DeathAnimMontage;
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SprintStart();
	void SprintEnd();
	void OnHealthChanged(float Health);
	void OnDeath();

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);

	
};
