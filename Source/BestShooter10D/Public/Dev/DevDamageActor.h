// Best Shooter Ever

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevDamageActor.generated.h"

UCLASS()
class BESTSHOOTER10D_API ADevDamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Magenta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
