// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UStaticMeshComponent* wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UPhysicsConstraintComponent* constraint = nullptr;
	
public:	
	ASprungWheel();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	void SetupConstraint();
};
