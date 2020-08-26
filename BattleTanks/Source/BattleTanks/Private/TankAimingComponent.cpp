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
	MoveBarrelAndTurret();
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
	Super::TickComponent(deltaTime, tickType, tickFunction);

	if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
		fireState = EFireState::Reloading;
	else if (IsBarrelMoving())
		fireState = EFireState::Aiming;
	else
		fireState = EFireState::Locked;
}

void UTankAimingComponent::MoveBarrelAndTurret()
{
	if (!ensure(m_barrel && m_turret))
		return; 

	auto barrelRotator = m_barrel->GetForwardVector().Rotation();
	auto deltaRotator = launchDirection.Rotation() - barrelRotator;
	if (FMath::Abs(deltaRotator.Yaw) > 180.f) {
		if (deltaRotator.Yaw > 0)
			deltaRotator.Yaw -= 360.f;
		else
			deltaRotator.Yaw += 360.f;
	}

	m_barrel->Elevate(deltaRotator.Pitch);
	m_turret->Rotate(deltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(m_barrel))
		return false;

	return !launchDirection.Equals(m_barrel->GetForwardVector(), 0.01f);
}
