// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SAnimInstance.generated.h"


class ASCharacter;

/**
 * 
 */
UCLASS()
class DBGA_API USAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "DBGA|Animation")
	bool PlayAttackMontage(UAnimMontage* MontageToPlay);

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	float GroundSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	bool bIsFalling;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	bool bShouldMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	FVector Velocity;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	bool bIsBlocking;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	TObjectPtr<ASCharacter> ControlledCharacter;

private:
	TObjectPtr<APawn> OwningPawn;
};
