// Best Shooter Ever


#include "Animations/ShooterEquipFinishedAN.h"

void UShooterEquipFinishedAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
	
}
