// Fill out your copyright notice in the Description page of Project Settings.

#include "TrainPlayerController.h"


void ATrainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTurret = GetControlledTurret();
	if (!ControlledTurret)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a turret"));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController is possesing a turret"));
}

void ATrainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATurret* ATrainPlayerController::GetControlledTurret() const
{
	return Cast<ATurret>(GetPawn());
}

bool ATrainPlayerController::GetSightRayHitLocation(FVector & OUTHitLocation) const
{
	//Find Crosshair Position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);

	//De-Project the screen position oof the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OUTHitLocation);
	}

	return true;
}

void ATrainPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTurret()) { return; }

	FVector HitLocation; // Out preameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTurret()->AimAt(HitLocation);
	}
}

bool ATrainPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation;	//TODO: Discard
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATrainPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation,EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}
