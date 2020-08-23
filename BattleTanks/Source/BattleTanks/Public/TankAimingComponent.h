// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFireState : uint8
{
	Locked,
	Aiming,
	Reloading,
};

// Holds barrel's properties and Elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* m_barrel = nullptr;
	UTankTurret* m_turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFireState fireState = EFireState::Aiming;

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *barrel, UTankTurret *turret);

public:
	// Aims at location
	void AimAt(const FVector& hitLocation, float launchSpeed);

private:
	// Moves barrel towards launch direction
	void MoveBarrel(const FVector& launchDirection);

	// Moves turret towards launch direction
	void MoveTurret(const FVector& launchDirection);
};
