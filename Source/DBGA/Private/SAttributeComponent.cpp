// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsFullMana() const
{
	return Mana >= MaxMana;
}

void USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Value)
{
	Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Value);
}

void USAttributeComponent::ApplyManaChange(AActor* InstigatorActor, float Value)
{
	Mana = FMath::Clamp(Mana + Value, 0.0f, MaxMana);

	OnManaChanged.Broadcast(InstigatorActor, this, Mana, Value);
}

#if WITH_EDITOR
void USAttributeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = (PropertyChangedEvent.Property != nullptr)
		? PropertyChangedEvent.Property->GetFName() 
		: NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(USAttributeComponent, MaxHealth))
	{
		Health = FMath::Clamp(Health, 0.0f, MaxHealth);
	}
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USAttributeComponent, MaxMana))
	{
		Mana = FMath::Clamp(Mana, 0.0f, MaxMana);
	}
}
#endif