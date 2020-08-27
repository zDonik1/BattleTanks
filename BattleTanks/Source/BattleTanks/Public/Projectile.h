// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	class UProjectileMovementComponent* projectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UStaticMeshComponent* collisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UParticleSystemComponent* launchBlast = nullptr;

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Launches projectile
	void Launch(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
