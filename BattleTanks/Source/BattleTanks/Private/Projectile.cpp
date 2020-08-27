// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	projectileMovement->bAutoActivate = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	explosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

void AProjectile::Launch(float speed)
{
	projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovement->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor,
	UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse();
}
