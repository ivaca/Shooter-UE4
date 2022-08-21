// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterCoreTypes.h"
#include "ShooterHealthComponent.generated.h"




UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BESTSHOOTER10D_API UShooterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShooterHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category="Health")
	bool IsDead() const { return Health <= 0.0f; }

	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealthPercent()const{return  Health/MaxHealth;};

	
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin="1", ClampMax="100"))
	float MaxHealth = 100.0f;

	
private:

	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);
};
