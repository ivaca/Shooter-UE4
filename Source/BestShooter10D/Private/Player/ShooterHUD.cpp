// Best Shooter Ever


#include "Player/ShooterHUD.h"

#include "Blueprint/UserWidget.h"

void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if(PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}

}
