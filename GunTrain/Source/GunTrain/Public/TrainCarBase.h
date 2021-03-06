// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TrainCarBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTrainCarDelegate);

UCLASS()
class GUNTRAIN_API ATrainCarBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATrainCarBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	//Return current health as a percent of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTrainCarDelegate OnDeath;
};
