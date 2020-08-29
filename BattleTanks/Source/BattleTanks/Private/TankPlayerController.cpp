// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* pawn)
{
	Super::SetPawn(pawn);

	if (!pawn)
		return;

	controlledTank = Cast<ATank>(pawn);
	if (!ensure(controlledTank))
		return;

	aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComponent))
		FoundAimingComponent(aimingComponent);

	controlledTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(controlledTank))
		return;

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
		aimingComponent->AimAt(hitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& o_hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation(viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation);
	FVector lookDirection;
	if (!GetLookDirection(screenLocation, lookDirection))
		return false;

	return GetLookVectorHitLocation(lookDirection, o_hitLocation);
}

bool ATankPlayerController::GetLookDirection(const FVector2D& screenLocation, FVector& o_lookDirection) const
{
	FVector worldLocation; // dummy variable
	return DeprojectScreenPositionToWorld(
		screenLocation.X, screenLocation.Y,
		worldLocation, o_lookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& lookDirection, FVector& o_hitLocation) const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	bool success = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility
	);

	if (!success) {
		o_hitLocation = FVector(0.0);
		return false;
	}

	o_hitLocation = hitResult.Location;

	return true;
}
