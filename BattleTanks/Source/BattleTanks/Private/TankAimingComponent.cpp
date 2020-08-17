// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* l_barrel)
{
	barrel = l_barrel;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(const FVector& hitLocation, float launchSpeed)
{
	if (!barrel)
		return;

	FVector launchVelocity(0.0);
	FVector startLocation = barrel->GetSocketLocation(FName("ProjectileLaunch"));
	auto success = UGameplayStatics::SuggestProjectileVelocity(
		this, launchVelocity, startLocation, hitLocation, launchSpeed, 
		false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (!success)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *launchVelocity.GetSafeNormal().ToString());
}

