// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSpell.h"
#include "STeleportSpell.generated.h"

/**
 * 
 */
UCLASS()
class DBGA_API ASTeleportSpell : public ASSpell
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTeleportSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	TObjectPtr<UProjectileMovementComponent> SpellMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell|Effect")
	TObjectPtr<UNiagaraSystem> HitNiagaraSystem;

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void SpellEnded(FVector Location) override;

private:
	void Teleport();
};
