// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(constraint);

	wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	wheel->SetupAttachment(RootComponent);

	mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	mass->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor()) {
		UE_LOG(LogTemp, Warning, TEXT("parent not null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("parent is null"));
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

