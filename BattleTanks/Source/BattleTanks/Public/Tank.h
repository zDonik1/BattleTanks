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
	class UTankAimingComponent* tankAimingComponent = nullptr;
	UTankBarrel* m_barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, Category = Firing)
		float launchSpeed = 10000; // cm/s = 100 m/s

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(const FVector &hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(class UTankTurret* turret);

	UFUNCTION(BlueprintCallable, Category = Action)
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
