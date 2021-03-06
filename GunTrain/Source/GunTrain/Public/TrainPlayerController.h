// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TrainPlayerController.generated.h"

class UAimingComponent;

/**
 * 
 */
UCLASS()
class GUNTRAIN_API ATrainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UAimingComponent* AimCompRef);

private:
	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OUTHitLocation) const;
	
	//Start the turret moving the barrel so that a shot would aim where the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = .5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = .30;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;


};
