// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float crossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float crossHairYLocation = 0.4f;

	UPROPERTY(EditDefaultsOnly)
		float lineTraceRange = 1000000; // cm = 10 km
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	class ATank* GetControlledTank() const;
	
	// Moving the barrel to aim to crosshair position
	void AimTowardsCrosshair();

	// Getting hit location of crosshair
	bool GetSightRayHitLocation(FVector &o_hitLocation) const;

	// Calculating look direction through crosshair
	bool GetLookDirection(const FVector2D &screenLocation, FVector &o_lookDirection) const;

	// Calculating hit location by line tracing
	bool GetLookVectorHitLocation(const FVector &lookDirection, FVector& o_hitLocation) const;
};
