// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.f, 1.f);
	auto deltaElevation = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newElevation = GetRelativeRotation().Pitch + deltaElevation;
	auto clampedElevation = FMath::Clamp(newElevation, minElevation, maxElevation);
	SetRelativeRotation(FRotator(clampedElevation, 0.f, 0.f));
}