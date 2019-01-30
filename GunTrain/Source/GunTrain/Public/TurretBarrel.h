// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GUNTRAIN_API UTurretBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxElevationDegrees = 40;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinElevationDegrees = 0;

};
