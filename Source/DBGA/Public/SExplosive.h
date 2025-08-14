// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosive.generated.h"

class URadialForceComponent;

UCLASS()
class DBGA_API ASExplosive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Explosive")
	TObjectPtr<UStaticMeshComponent> ExplosiveMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Explosive")
	TObjectPtr<URadialForceComponent> ExplosiveRadialForceComponent;
};
