// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *hitLocation.ToString());

		// If collisions occurs, aim tank towards collision point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& o_hitLocation) const
{
	o_hitLocation = FVector(1.0);
	return true;
}
