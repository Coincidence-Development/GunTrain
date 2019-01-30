// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "TurretBarrel.h"
#include "Projectile_Base.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
}