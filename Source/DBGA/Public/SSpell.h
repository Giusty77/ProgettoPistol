// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSpell.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;


UENUM(BlueprintType)
enum class ESpellType : uint8
{
	Projectile UMETA(DisplayName = "Projectile"),
	AreaOfEffect UMETA(DisplayName = "Area Of Effect")
};


UCLASS()
class DBGA_API ASSpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "DBGA|Spell")
	const ESpellType GetSpellType() const { return SpellType; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	TObjectPtr<USphereComponent> SpellCollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell|Effect")
	TObjectPtr<UNiagaraComponent> NiagaraEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell|Effect")
	TObjectPtr<UNiagaraSystem> NiagaraSystem;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	float SpellDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	ESpellType SpellType;

protected:
	virtual void SpellEnded(FVector Location);
};
