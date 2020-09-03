// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	componentAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(
		FName("ComponentAxleConstraint"));
	SetRootComponent(componentAxleConstraint);

	axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	axle->SetupAttachment(componentAxleConstraint);

	wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	wheel->SetupAttachment(axle);

	axleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(
		FName("AxleWheelConstraint"));
	axleWheelConstraint->SetupAttachment(axle);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	totalForceMagnitude = 0;
}

void ASprungWheel::AddDrivingForce(float forceMagnitude)
{
	totalForceMagnitude += forceMagnitude;
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	wheel->SetNotifyRigidBodyCollision(true);
	wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	
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

	componentAxleConstraint->SetConstrainedComponents(parentRootComp, NAME_None, axle, NAME_None);
	axleWheelConstraint->SetConstrainedComponents(axle, NAME_None, wheel, NAME_None);
}

void ASprungWheel::ApplyForce()
{
	wheel->AddForce(axle->GetForwardVector() * totalForceMagnitude);
}

void ASprungWheel::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor,
	UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	ApplyForce();
}

