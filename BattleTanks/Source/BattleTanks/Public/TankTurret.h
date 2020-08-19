// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSecond = 20.f;

public:
	/**
	* @brief Rotate the barrel with some relative speed
	* @params relativeSpeed: -1.0 is max downward speed, 1.0 is max upward speed
	*/
	void Rotate(float relativeSpeed);
};
