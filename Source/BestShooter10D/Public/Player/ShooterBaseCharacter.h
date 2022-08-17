// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
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
	
	float InitialSpeed;
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SprintStart();
	void SprintEnd();

	
};
