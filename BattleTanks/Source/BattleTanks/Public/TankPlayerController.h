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
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	class ATank* GetControlledTank() const;
	
	// Moving the barrel to aim to crosshair position
	void AimTowardsCrosshair();

	// Line tracing to hit location
	bool GetSightRayHitLocation(FVector &o_hitLocation) const;
};
