// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	UTankTrack* m_leftTrack = nullptr;
	UTankTrack* m_rightTrack = nullptr;
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveForward(float axis);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveRight(float axis);

	void RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed) override;
};
