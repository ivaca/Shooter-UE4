// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "ShooterCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/ShooterHealthComponent.h"
#include "Components/ShooterWeaponComponent.h"
#include "ShooerPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESTSHOOTER10D_API UShooerPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetAmmoUIData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerSpectating() const;
private:
	UShooterHealthComponent* GetHealthComponent() const;
	UShooterWeaponComponent* GetWeaponComponent() const;
};
