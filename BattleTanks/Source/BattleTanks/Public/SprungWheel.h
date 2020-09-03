// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()

private:
	float totalForceMagnitude = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* componentAxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* axleWheelConstraint = nullptr;

public:
	ASprungWheel();

	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float forceMagnitude);

protected:
	virtual void BeginPlay() override;

private:
	void SetupConstraint();
	void ApplyForce();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor,
			UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
