// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "ShooterCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "ShooterPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BESTSHOOTER10D_API UShooterPlayerHUDWidget : public UUserWidget
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

};
