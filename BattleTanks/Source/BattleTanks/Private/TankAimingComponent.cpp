// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* l_barrel)
{
	barrel = l_barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* l_turret)
{
	turret = l_turret;
}

void UTankAimingComponent::AimAt(const FVector& hitLocation, float launchSpeed)
{
	if (!barrel)
		return;

	FVector launchVelocity(0.0);
	FVector startLocation = barrel->GetSocketLocation(FName("ProjectileLaunch"));
	auto success = UGameplayStatics::SuggestProjectileVelocity(
		this, launchVelocity, startLocation, hitLocation, launchSpeed, 
		false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (!success)
		return;
	
	auto normalLaunchVelocity = launchVelocity.GetSafeNormal();
	MoveBarrel(normalLaunchVelocity);
	MoveTurret(normalLaunchVelocity);
}

void UTankAimingComponent::MoveBarrel(const FVector& launchDirection)
{
	auto barrelPitch = barrel->GetForwardVector().Rotation().Pitch;
	auto deltaPitch = launchDirection.Rotation().Pitch - barrelPitch;
	barrel->Elevate(deltaPitch);
}

void UTankAimingComponent::MoveTurret(const FVector& launchDirection)
{
	auto turretYaw = turret->GetForwardVector().Rotation().Yaw;
	auto deltaYaw = launchDirection.Rotation().Yaw - turretYaw;
	UE_LOG(LogTemp, Warning, TEXT("%f: deltaYaw: %f"), GetWorld()->GetTimeSeconds(), deltaYaw);
	turret->Rotate(deltaYaw);
}
