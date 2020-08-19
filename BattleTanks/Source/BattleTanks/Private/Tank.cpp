// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));

}

void ATank::AimAt(const FVector& hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* barrel)
{
	m_barrel = barrel;
	tankAimingComponent->SetBarrelReference(barrel);
}

void ATank::SetTurretReference(UTankTurret* turret)
{
	tankAimingComponent->SetTurretReference(turret);
}

void ATank::Fire()
{
	if (!m_barrel)
		return;

	auto projectileInstance = GetWorld()->SpawnActor<AProjectile>(
		projectile,
		m_barrel->GetSocketLocation(FName("ProjectileLaunch")),
		m_barrel->GetSocketRotation(FName("ProjectileLaunch"))
		);

	projectileInstance->Launch(launchSpeed);
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

