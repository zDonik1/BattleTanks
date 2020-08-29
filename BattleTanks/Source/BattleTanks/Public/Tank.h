// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 startingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 currentHealth = startingHealth;

public:
	FDeathDelegate OnDeath;

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	virtual float TakeDamage(float damageAmount, const FDamageEvent& damageEvent,
		AController* eventInstigator, AActor* damageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
