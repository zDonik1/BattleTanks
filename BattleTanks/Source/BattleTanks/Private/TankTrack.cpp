// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float throttle)
{
	DriveTrack(FMath::Clamp(throttle, -1.f, 1.f));
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	tankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::DriveTrack(float throttle)
{
	auto forceApplied = throttle * maxDrivingForce;
	auto wheels = GetWheels();
	auto forcePerWheel = forceApplied / wheels.Num();
	for (ASprungWheel* wheel : wheels) {
		wheel->AddDrivingForce(forcePerWheel);
	}
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> resultArray;
	TArray<USceneComponent*> children;
	GetChildrenComponents(true, children);
	for (auto* child : children) {
		auto spawnPointChild = Cast<USpawnPoint>(child);
		if (!spawnPointChild)
			continue;

		auto sprungWheel = Cast<ASprungWheel>(spawnPointChild->GetSpawnedActor());
		if (!sprungWheel)
			continue;

		resultArray.Add(sprungWheel);
	}
	return resultArray;
}
