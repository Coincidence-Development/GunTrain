// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "TurretBarrel.h"
#include "Projectile_Base.h"
#include "AimingComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
}

void ATurret::SetBarrelReference(UTurretBarrel * BarrelToSet)
{
	AimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATurret::SetTurretHeadReference(UTurretHead * TurretHeadToSet)
{
	AimingComponent->SetTurretHeadReference(TurretHeadToSet);
}

void ATurret::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATurret::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Fires"), Time);

	if (!Barrel) { return; }
	//Spawn Projectile at socket on barrel
	GetWorld()->SpawnActor<AProjectile_Base>(Projectile, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

