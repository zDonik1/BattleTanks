// Copyright EmbraceIT Ltd.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	m_leftTrack = leftTrack;
	m_rightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float axis)
{
	// TODO: some day, fix the issue with double speed when fly-by-wire and manual contorls are used together
	if (!ensure(m_leftTrack && m_rightTrack))
		return;

	m_leftTrack->SetThrottle(axis);
	m_rightTrack->SetThrottle(axis);
}

void UTankMovementComponent::IntendMoveRight(float axis)
{
	// TODO: some day, fix the issue with double speed when fly-by-wire and manual contorls are used together
	if (!ensure(m_leftTrack && m_rightTrack))
		return;

	m_leftTrack->SetThrottle(-axis);
	m_rightTrack->SetThrottle(axis);
}

void UTankMovementComponent::RequestDirectMove(const FVector& moveVelocity, bool bForceMaxSpeed)
{
	auto tankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto forwardMoveIntention = moveVelocity.GetSafeNormal(); // vector where the tank should move to
	IntendMoveForward(FVector::DotProduct(tankForwardVector, forwardMoveIntention));
	IntendMoveRight(FVector::CrossProduct(tankForwardVector, forwardMoveIntention).Z);
}
