// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxDegreesPerSecond = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float minElevation = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float maxElevation = 35.f;
	
public:
	/** 
	* @brief Elevates the barrel with some relative speed
	* @params relativeSpeed: -1.0 is max downward speed, 1.0 is max upward speed
	*/
	void Elevate(float relativeSpeed);
};
