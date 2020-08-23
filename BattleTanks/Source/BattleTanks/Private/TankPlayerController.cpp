// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	controlledTank = Cast<ATank>(GetPawn());
	// finding component instead of getting from tank, since there is a race condition
	// ... between when BeginPlay is called on PlayerController and Tank
	auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent))
		return;
	
	FoundAimingComponent(aimingComponent);
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(controlledTank))
		return;

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
		controlledTank->GetAimComponent()->AimAt(hitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& o_hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation(viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation);
	FVector lookDirection;
	if (!GetLookDirection(screenLocation, lookDirection))
		return false;

	if (!GetLookVectorHitLocation(lookDirection, o_hitLocation))
		return false;

	return true;
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
