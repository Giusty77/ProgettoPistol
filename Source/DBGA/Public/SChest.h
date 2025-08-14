// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "Curves/CurveFloat.h"
#include "SChest.generated.h"

UCLASS()
class DBGA_API ASChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Mesh")
	TObjectPtr<UStaticMeshComponent> BodyMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Mesh")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	float LidInterpolationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	float LidTargetAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	bool bIsOpen;

public:
	void OnInteract_Implementation(AActor* InteractingActor) override;

private:
	bool bIsAnimated;
	float CurrentLerpAlpha;
};
