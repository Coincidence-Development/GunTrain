// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

class UTurretBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNTRAIN_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

public:	
	void SetBarrelReference(UTurretBarrel* BarrelToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UTurretBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
