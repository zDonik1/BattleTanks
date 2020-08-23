// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// finding component instead of getting from tank, since there is a race condition
	// ... between when BeginPlay is called on PlayerController and Tank
	aimComponent = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (!ensure(playerTank))
		return;

	MoveToActor(playerTank, acceptanceRadius);

	if (!ensure(aimComponent))
		return;

	aimComponent->AimAt(playerTank->GetActorLocation());
	aimComponent->Fire();
}
