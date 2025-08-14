// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComponent, float, NewValue, float, DeltaValue);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DBGA_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsFullMana() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyHealthChange(AActor* InstigatorActor, float Value);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyManaChange(AActor* InstigatorActor, float Value);

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnManaChanged;

private:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 100.0, ClampMax = 100.0))
	float Health = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 100.0, ClampMax = 100.0))
	float MaxHealth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 100.0, ClampMax = 100.0))
	float Mana = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 100.0, ClampMax = 100.0))
	float MaxMana = 0.0f;
};
