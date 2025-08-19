// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"
#include "SCharacter.h"
#include "SAnimInstance.h"
#include "EnhancedPlayerInput.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "SWeapon.h"


void ASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);

	REGISTER_INPUT_ACTION(EnhancedInputComponent, MoveActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, LookActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, JumpActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, ShootActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, InteractActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, Spell1ActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, Spell2ActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, Spell3ActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, Spell4ActionInput, ETriggerEvent::Triggered);
	REGISTER_INPUT_ACTION(EnhancedInputComponent, Spell5ActionInput, ETriggerEvent::Triggered);
}

void ASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InputMappingContext == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputMappingContext is not set!"));
		return;
	}

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->AddMappingContext(InputMappingContext, 0);

	ControlledCharacter = Cast<ASCharacter>(InPawn);
}

void ASPlayerController::OnMoveActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;

		const FVector Forward = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::X);
		const FVector Right = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

		const FVector2D MovementVector = Value.Get<FVector2D>();

		ControlledCharacter->AddMovementInput(Forward, MovementVector.X);
		ControlledCharacter->AddMovementInput(Right, MovementVector.Y);
	}
}

void ASPlayerController::OnLookActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		const FVector2D LookVector = Value.Get<FVector2D>();

		ControlledCharacter->AddControllerYawInput(LookVector.X);
		ControlledCharacter->AddControllerPitchInput(LookVector.Y);
	}
}

void ASPlayerController::OnJumpActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		if (Value.Get<bool>())
		{
			ControlledCharacter->Jump();
		}
		else
		{
			ControlledCharacter->StopJumping();
		}
	}
}


void ASPlayerController::OnShootActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		USkeletalMeshComponent* MeshComp = ControlledCharacter->GetMesh();
		if (!MeshComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("MeshComp is null!"));
			return;
		}

		USAnimInstance* AnimInstance = Cast<USAnimInstance>(MeshComp->GetAnimInstance());
		if (!AnimInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("AnimInstance is null!"));
			return;
		}

		if (!ControlledCharacter->AttackMontage)
		{
			UE_LOG(LogTemp, Warning, TEXT("AttackMontage is not set!"));
			return;
		}

		if (Value.Get<bool>())
		{
			FRotator TargetRotation(0.0f, ControlRotation.Yaw, 0.0f);

			ControlledCharacter->SetActorRotation(TargetRotation);

			AnimInstance->PlayAttackMontage(ControlledCharacter->AttackMontage);
		}
	}
}

void ASPlayerController::OnInteractActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->OnInteract();
	}
}

void ASPlayerController::OnSpell1ActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->SetCurrentSpellIndex(0);
	}
}

void ASPlayerController::OnSpell2ActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->SetCurrentSpellIndex(1);
	}
}

void ASPlayerController::OnSpell3ActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->SetCurrentSpellIndex(2);
	}
}

void ASPlayerController::OnSpell4ActionInput(const FInputActionValue& Value)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->SetCurrentSpellIndex(3);
	}
}

void ASPlayerController::OnSpell5ActionInput(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed 5"));

	if (ControlledCharacter && ControlledCharacter->WeaponComponent)
	{
		ControlledCharacter->WeaponComponent->ToggleVisibility();
		UE_LOG(LogTemp, Warning, TEXT("Visibility Weapon"));

		if (ControlledCharacter->WeaponComponent->GetVisibility())
		{
			ControlledCharacter->SetCurrentSpellIndex(4);
		}
	}

	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("PRESSING 5"));
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Emerald, DebugMessage);
	}

	
}