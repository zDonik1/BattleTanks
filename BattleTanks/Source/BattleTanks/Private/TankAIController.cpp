// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank) {
		MoveToActor(playerTank, acceptanceRadius);

		auto controlledTank = Cast<ATank>(GetPawn());
		auto aimComponent = controlledTank->GetAimComponent();
		if (!ensure(aimComponent))
			return;

		aimComponent->AimAt(playerTank->GetActorLocation());
		controlledTank->Fire();
	}
}
