// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"


#define REGISTER_INPUT_ACTION(EnchangedInputController, InputAction, TriggerEvent) \
if (InputAction == nullptr) { UE_LOG(LogTemp, Warning, TEXT("InputAction is not set!")); } \
else { EnchangedInputController->BindAction(InputAction, TriggerEvent, this, &ASPlayerController::On##InputAction); }


class ASCharacter;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class DBGA_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Character")
	TObjectPtr<ASCharacter> ControlledCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Input")
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> MoveActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> LookActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> JumpActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> ShootActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> InteractActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> Spell1ActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> Spell2ActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> Spell3ActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> Spell4ActionInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DBGA|Input")
	TObjectPtr<UInputAction> Spell5ActionInput;

protected:
	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnMoveActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnLookActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnJumpActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnShootActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnInteractActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnSpell1ActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnSpell2ActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnSpell3ActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnSpell4ActionInput(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Input")
	void OnSpell5ActionInput(const FInputActionValue& Value);
};
