// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	m_leftTrack = leftTrack;
	m_rightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float axis)
{
	if (!m_leftTrack || !m_rightTrack)
		return;

	m_leftTrack->SetThrottle(axis);
	m_rightTrack->SetThrottle(axis);
}

void UTankMovementComponent::IntendMoveRight(float axis)
{
	if (!m_leftTrack || !m_rightTrack)
		return;

	m_leftTrack->SetThrottle(axis);
	m_rightTrack->SetThrottle(-axis);
}
