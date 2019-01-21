// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::AimAt(FVector HitLocation)
{
	auto OurTurretName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *OurTurretName, *HitLocation.ToString());
}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

