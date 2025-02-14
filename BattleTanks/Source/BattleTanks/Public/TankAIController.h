// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	ATank* controlledTank = nullptr;
	ATank* playerTank = nullptr;
	class UTankAimingComponent* aimComponent = nullptr;

	// How close AI tank should be to player before stopping in cm
	UPROPERTY(EditDefaultsOnly)
		float acceptanceRadius = 8000.f;
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void SetPawn(APawn* pawn) override;

	UFUNCTION()
		void OnTankDeath();
};
