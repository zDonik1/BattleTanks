// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.f, 1.f);
	auto deltaRotation = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newRotation = GetRelativeRotation().Yaw + deltaRotation;
	SetRelativeRotation(FRotator(0.f, newRotation, 0.f));
}
