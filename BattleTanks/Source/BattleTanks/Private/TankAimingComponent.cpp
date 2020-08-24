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

	FVector startLocation = m_barrel->GetSocketLocation(FName("ProjectileLaunch"));
	auto success = UGameplayStatics::SuggestProjectileVelocity(
		this, launchDirection, startLocation, hitLocation, launchSpeed, 
		false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (!success)
		return;
	
	launchDirection = launchDirection.GetSafeNormal();
	MoveBarrel();
	MoveTurret();
}

void UTankAimingComponent::Fire()
{
	if (!ensure(m_barrel && projectile))
		return;

	if (fireState == EFireState::Reloading)
		return;

	auto projectileInstance = GetWorld()->SpawnActor<AProjectile>(
		projectile,
		m_barrel->GetSocketLocation(FName("ProjectileLaunch")),
		m_barrel->GetSocketRotation(FName("ProjectileLaunch"))
		);

	projectileInstance->Launch(launchSpeed);
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float deltaTime, ELevelTick tickType, 
	FActorComponentTickFunction* tickFunction)
{
	if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
		fireState = EFireState::Reloading;
	else if (IsBarrelMoving())
		fireState = EFireState::Aiming;
	else
		fireState = EFireState::Locked;
}

void UTankAimingComponent::MoveBarrel()
{
	if (!ensure(m_barrel && m_turret))
		return; 

	auto barrelPitch = m_barrel->GetForwardVector().Rotation().Pitch;
	auto deltaPitch = launchDirection.Rotation().Pitch - barrelPitch;
	m_barrel->Elevate(deltaPitch);
}

void UTankAimingComponent::MoveTurret()
{
	if (!ensure(m_barrel && m_turret))
		return;

	auto turretYaw = m_turret->GetForwardVector().Rotation().Yaw;
	auto deltaYaw = launchDirection.Rotation().Yaw - turretYaw;
	m_turret->Rotate(deltaYaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(m_barrel))
		return false;

	return !launchDirection.Equals(m_barrel->GetForwardVector(), 0.01f);
}
