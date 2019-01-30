// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurretBarrel.h"
#include "TurretHead.h"
#include "Projectile_Base.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UAimingComponent::Initialise(UTurretHead * TurretHeadToSet, UTurretBarrel * BarrelToSet)
{
	TurretHead = TurretHeadToSet;
	Barrel = BarrelToSet;
}

void UAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OUTLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OUTLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity( this, OUTLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OUTLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
		//No aim solution found
}

void UAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		//Spawn Projectile at socket on barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile_Base>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}
}

EFiringState UAimingComponent::GetFiringState() const { return FiringState; }
int32 UAimingComponent::GetRoundsLeft() const { return RoundsLeft; }

void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(TurretHead && Barrel)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	//Always Take Shortest Route
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		TurretHead->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		TurretHead->Rotate(-DeltaRotator.Yaw);
	}
}

bool UAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

