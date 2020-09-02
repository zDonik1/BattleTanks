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
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	auto parentActor = GetAttachParentActor();
	if (!ensure(GetAttachParentActor()))
		return;

	auto parentRootComp = Cast<UPrimitiveComponent>(parentActor->GetRootComponent());
	if (!ensure(parentRootComp))
		return;

	constraint->SetConstrainedComponents(parentRootComp, NAME_None, wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

