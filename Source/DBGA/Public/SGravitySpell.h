// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAreaSpell.h"
#include "SGravitySpell.generated.h"


class UDecalComponent;
class UMaterialInterface;
class URadialForceComponent;

/**
 * 
 */
UCLASS()
class DBGA_API ASGravitySpell : public ASAreaSpell
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASGravitySpell();

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BindSpellCollisionComponent() override;
	virtual void UnbindSpellCollisionComponent() override;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	float SpellStrength;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell|Effect")
	TObjectPtr<UNiagaraSystem> OverlapNiagaraSystem;

private:
	UPROPERTY()
	TMap<AActor*, float> AffectedActors;
};
