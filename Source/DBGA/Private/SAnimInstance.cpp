// Fill out your copyright notice in the Description page of Project Settings.


#include "SAnimInstance.h"
#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void USAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GroundSpeed = 0.0f;
	bIsFalling = false;

	// Get the owning pawn
	OwningPawn = TryGetPawnOwner();
	if (OwningPawn)
	{
		ControlledCharacter = Cast<ASCharacter>(OwningPawn);

		UE_LOG(LogTemp, Log, TEXT("Owning Pawn: %s"), *OwningPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning Pawn is null!"));
	}
}

void USAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningPawn)
	{
		Velocity = OwningPawn->GetVelocity();

		FVector GroundVelocity = Velocity;
		GroundVelocity.Z = 0;

		GroundSpeed = GroundVelocity.Length();

		bIsFalling = ControlledCharacter->GetCharacterMovement()->IsFalling();

		FVector Acceleration = ControlledCharacter->GetCharacterMovement()->GetCurrentAcceleration();

		bShouldMove = (GroundSpeed > 3.0f && Acceleration.SquaredLength() > 0.01f);


		bIsBlocking = ControlledCharacter->bIsBlocking;
	}
}

bool USAnimInstance::PlayAttackMontage(UAnimMontage* MontageToPlay)
{
	if (MontageToPlay && !Montage_IsPlaying(MontageToPlay))
	{
		Montage_Play(MontageToPlay);

		return true;
	}

	return false;
}