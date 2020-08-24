// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float throttle)
{
	auto forceApplied = GetForwardVector() * throttle * maxDrivingForce;
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

void UTankTrack::BeginPlay()
{
	tankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::TickComponent(float deltaTime, ELevelTick tickType,
	FActorComponentTickFunction* tickFunction)
{
	Super::TickComponent(deltaTime, tickType, tickFunction);

	if (!ensure(tankRootMesh))
		return;

	auto rightVector = GetRightVector();
	auto horizontalSlipSpeed = FVector::DotProduct(GetComponentVelocity(), rightVector);
	auto correctionAcceleration = horizontalSlipSpeed / deltaTime * -rightVector;
	auto correctionForce = correctionAcceleration * tankRootMesh->GetMass() / 2; // 2 tracks
	tankRootMesh->AddForce(correctionForce);
}
