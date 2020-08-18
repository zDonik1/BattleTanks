// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSecond = 15.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float minElevation = 0.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxElevation = 35.f;
	
public:
	void Elevate(float degreesPerSecond);
};
