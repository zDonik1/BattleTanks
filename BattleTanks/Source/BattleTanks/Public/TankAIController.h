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
	// How close AI tank should be to player before stopping in cm
	UPROPERTY(EditDefaultsOnly)
		float acceptanceRadius = 3000.f;
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
};
