// Fill out your copyright notice in the Description page of Project Settings.


#include "SChest.h"

// Sets default values
ASChest::ASChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	RootComponent = BodyMeshComponent;

	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("List Mesh"));
	LidMeshComponent->SetupAttachment(BodyMeshComponent);

	LidInterpolationSpeed = 2.0f;
	bIsAnimated = false;
	bIsOpen = false;
	CurrentLerpAlpha = 0.0f;
}

// Called when the game starts or when spawned
void ASChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAnimated)
	{
		CurrentLerpAlpha += DeltaTime * LidInterpolationSpeed;

		const float Alpha = FMath::Clamp(CurrentLerpAlpha, 0.0f, 1.0f);

		float TargetAngle;
		float StartAngle;
		if (bIsOpen)
		{
			TargetAngle = LidTargetAngle;
			StartAngle = 0.0f;
		}
		else
		{
			TargetAngle = 0.0f;
			StartAngle = LidTargetAngle;
		}

		const float NewAngle = FMath::Lerp(StartAngle, TargetAngle, Alpha);

		LidMeshComponent->SetRelativeRotation(FRotator(NewAngle, 0.0f, 0.0f));

		if (Alpha >= 0.999f)
		{
			CurrentLerpAlpha = 0.0f;
			bIsAnimated = false;
		}
	}
}

void ASChest::OnInteract_Implementation(AActor* InteractingActor)
{
	if (CurrentLerpAlpha > 0.0f)
	{
		return;
	}

	bIsOpen = !bIsOpen;
	CurrentLerpAlpha = 0.0f;
	bIsAnimated = true;
}
