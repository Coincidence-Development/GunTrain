// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainCarBase.h"

// Sets default values
ATrainCarBase::ATrainCarBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATrainCarBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATrainCarBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	auto DamageToApply = FMath::Clamp<int32>(Damage, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) { OnDeath.Broadcast(); }
	return DamageToApply;
}

float ATrainCarBase::GetHealthPercent() const { return (float)CurrentHealth / (float)StartingHealth; }
