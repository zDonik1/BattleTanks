// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel* barrel, UTankTurret* turret)
{
	m_barrel = barrel;
	m_turret = turret;
}

void UTankAimingComponent::AimAt(const FVector& hitLocation)
{
	if (!ensure(m_barrel && m_turret))
		return;

	FVector launchVelocity(0.0);
	FVector startLocation = m_barrel->GetSocketLocation(FName("ProjectileLaunch"));
	auto success = UGameplayStatics::SuggestProjectileVelocity(
		this, launchVelocity, startLocation, hitLocation, launchSpeed, 
		false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (!success)
		return;
	
	auto normalLaunchVelocity = launchVelocity.GetSafeNormal();
	MoveBarrel(normalLaunchVelocity);
	MoveTurret(normalLaunchVelocity);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(m_barrel && projectile))
		return;

	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
	if (!isReloaded)
		return;

	auto projectileInstance = GetWorld()->SpawnActor<AProjectile>(
		projectile,
		m_barrel->GetSocketLocation(FName("ProjectileLaunch")),
		m_barrel->GetSocketRotation(FName("ProjectileLaunch"))
		);

	projectileInstance->Launch(launchSpeed);
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::MoveBarrel(const FVector& launchDirection)
{
	if (!ensure(m_barrel && m_turret))
		return; 

	auto barrelPitch = m_barrel->GetForwardVector().Rotation().Pitch;
	auto deltaPitch = launchDirection.Rotation().Pitch - barrelPitch;
	m_barrel->Elevate(deltaPitch);
}

void UTankAimingComponent::MoveTurret(const FVector& launchDirection)
{
	if (!ensure(m_barrel && m_turret))
		return;

	auto turretYaw = m_turret->GetForwardVector().Rotation().Yaw;
	auto deltaYaw = launchDirection.Rotation().Yaw - turretYaw;
	m_turret->Rotate(deltaYaw);
}
