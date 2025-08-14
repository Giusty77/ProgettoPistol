// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class UMySkeletalMeshComponent;
class USphereComponent;

UCLASS()
class DBGA_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Gun")
	TObjectPtr<USkeletalMeshComponent> MeshGun;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Gun")
	TObjectPtr<UStaticMeshComponent> Mesh;
	*/
	//UPROPERTY(EditDefaultsOnly)
	//TObjectPtr<UMySkeletalMeshComponent> WeaponComponents;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Gun")
	TObjectPtr<USkeletalMeshComponent> MeshGun;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	TObjectPtr<USphereComponent> CollisionComponent;

};
