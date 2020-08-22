// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrelRef(UTankBarrel* barrel)
{
	m_barrel = barrel;
}

void ATank::AimAt(const FVector& hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	if (!m_barrel)
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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

