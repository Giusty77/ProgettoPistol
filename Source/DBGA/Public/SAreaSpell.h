// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSpell.h"
#include "SAreaSpell.generated.h"



class UDecalComponent;
class UMaterialInterface;

/**
 * 
 */
UCLASS()
class DBGA_API ASAreaSpell : public ASSpell
{
	GENERATED_BODY()

public:
	ASAreaSpell();

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DBGA|Spell")
	float GetSpellRadius() const;

	virtual float GetSpellRadius_Implementation() const { return SpellRadius; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DBGA|Spell")
	float GetSpellDistance() const;

	virtual float GetSpellDistance_Implementation() const { return SpellDistance; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DBGA|Spell")
	UMaterialInterface* GetDecalComponentMaterial() const;

	virtual UMaterialInterface* GetDecalComponentMaterial_Implementation() const { return DecalComponentMaterial; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void BindSpellCollisionComponent() {}
	virtual void UnbindSpellCollisionComponent() {}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	float SpellDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	float SpellRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	TObjectPtr<UMaterialInterface> DecalComponentMaterial;
};
