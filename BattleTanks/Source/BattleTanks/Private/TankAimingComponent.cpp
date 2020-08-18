// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* l_barrel)
{
	barrel = l_barrel;
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
	
	MoveBarrel(launchVelocity.GetSafeNormal());
}

void UTankAimingComponent::MoveBarrel(const FVector& launchDirection)
{
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = launchDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;
	barrel->Elevate(5.0f);
}

