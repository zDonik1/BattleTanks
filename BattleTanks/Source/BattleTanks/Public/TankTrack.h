// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* tankRootMesh = nullptr;
	float currentThrottle = 0.f;

	// Max driving force in kg*cm*s^-2
	UPROPERTY(EditDefaultsOnly)
		float maxDrivingForce = 40000000.f;

public:
	UTankTrack();

	// Sets a throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);


private:
	void BeginPlay() override;
	
	void DriveTrack();
	void ApplySidewaysForce();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor,
			UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit);
};
