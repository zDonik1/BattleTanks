// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UTankBarrel* m_barrel = nullptr;

	double lastFireTime = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float launchSpeed = 10000; // cm/s = 100 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing);
	float reloadTimeInSeconds = 3.f;

protected:
	UPROPERTY(BlueprintReadOnly)
		class UTankAimingComponent* tankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
		class UTankMovementComponent* tankMovementComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	void SetBarrelRef(UTankBarrel* barrel);
	void AimAt(const FVector& hitLocation);

	UFUNCTION(BlueprintCallable, Category = Action)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
