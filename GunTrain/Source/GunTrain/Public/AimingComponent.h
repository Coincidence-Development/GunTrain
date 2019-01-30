// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

class UTurretBarrel;
class UTurretHead;
class AProjectile_Base;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNTRAIN_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTurretHead* TurretHeadToSet, UTurretBarrel* BarrelToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile_Base> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float ReloadTimeInSeconds = 3.0;

	UTurretBarrel* Barrel = nullptr;
	UTurretHead* TurretHead = nullptr;

	double LastFireTime = 0;
	FVector AimDirection;

	UPROPERTY(EditAnywhere, Category = "Firing")
		int32 RoundsLeft = 3;
};
