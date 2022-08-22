// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterHUD.generated.h"

/**
 * 
 */
UCLASS()
class BESTSHOOTER10D_API AShooterHUD : public AHUD
{
	GENERATED_BODY()
public:
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;
};
