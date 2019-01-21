// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

class UAimingComponent;
class UTurretBarrel;
class UTurretHead;

UCLASS()
class GUNTRAIN_API ATurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAimingComponent* AimingComponent = nullptr;

public:	
	UFUNCTION(BlueprintCallable, Category = SetUp)
	void SetBarrelReference(UTurretBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = SetUp)
	void SetTurretHeadReference(UTurretHead* TurretHeadToSet);

	void AimAt(FVector HitLocation);

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;
};
