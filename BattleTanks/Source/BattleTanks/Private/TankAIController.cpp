// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AIController not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *(controlledTank->GetName()));
	}

	auto playerTank = GetPlayerTank();

	if (!playerTank) {
		UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank")) ;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(playerTank->GetName()));
	}
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	auto playerTank = GetPlayerTank();
	if (playerTank) {
		GetControlledTank()->AimAt(playerTank->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
