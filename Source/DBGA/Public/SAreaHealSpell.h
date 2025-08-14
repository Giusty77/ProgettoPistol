// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAreaSpell.h"
#include "SAreaHealSpell.generated.h"

/**
 * 
 */
UCLASS()
class DBGA_API ASAreaHealSpell : public ASAreaSpell
{
	GENERATED_BODY()

public:
	ASAreaHealSpell();

protected:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BindSpellCollisionComponent() override;
	virtual void UnbindSpellCollisionComponent() override;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	float SpellEffectPerSecond;

private:
	TArray<AActor*> OverlappedActors;
	float TimeAccumulated;
};
