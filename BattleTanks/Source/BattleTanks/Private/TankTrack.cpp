// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), throttle);
}