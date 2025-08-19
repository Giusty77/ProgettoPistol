// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

UCLASS()
class DBGA_API ASWeapon : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "DBGA| Weapon")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "DBGA|Weapon")
	void ToggleVisibility();

	UFUNCTION(BlueprintCallable, Category = "DBGA|Weapon")
	void Attach(ASCharacter* Parent);
	
	UFUNCTION(BlueprintCallable, Category = "DBGA|Weapon")
	bool GetVisibility();
};
