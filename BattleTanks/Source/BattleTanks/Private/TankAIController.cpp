// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
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

	if (aimComponent->GetFireState() == EFireState::Locked)
		aimComponent->Fire();
}

void ATankAIController::SetPawn(APawn* pawn)
{
	Super::SetPawn(pawn);

	if (!pawn)
		return;

	controlledTank = Cast<ATank>(pawn);
	if (!ensure(controlledTank))
		return;

	aimComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	controlledTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}

void ATankAIController::OnTankDeath()
{
	controlledTank->DetachFromControllerPendingDestroy();
}
