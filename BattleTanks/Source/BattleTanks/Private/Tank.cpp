// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::AimAt(const FVector &hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* barrel)
{
	tankAimingComponent->SetBarrelReference(barrel);
}

void ATank::SetTurretReference(UTankTurret* turret)
{
	tankAimingComponent->SetTurretReference(turret);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("%f: Tank firing"), GetWorld()->GetTimeSeconds());
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

