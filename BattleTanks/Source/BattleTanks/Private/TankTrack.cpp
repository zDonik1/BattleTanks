// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp(currentThrottle + throttle, -1.f, 1.f);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	tankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::DriveTrack()
{
	auto forceApplied = GetForwardVector() * currentThrottle * maxDrivingForce;
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

void UTankTrack::ApplySidewaysForce()
{
	if (!ensure(tankRootMesh))
		return;

	auto rightVector = GetRightVector();
	auto horizontalSlipSpeed = FVector::DotProduct(GetComponentVelocity(), rightVector);
	auto correctionAcceleration = horizontalSlipSpeed / GetWorld()->GetDeltaSeconds() * -rightVector;
	auto correctionForce = correctionAcceleration * tankRootMesh->GetMass() / 2; // 2 tracks
	tankRootMesh->AddForce(correctionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0.f;
}
