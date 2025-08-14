// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InteractDistance = 100.0f;
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::OnInteract()
{
	static const float SphereCastRadius = 100.0f;

	UWorld* World = GetWorld();
	check(World);

	AActor* OwnerActor = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerActor->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector Start = EyeLocation;
	const FVector End = EyeLocation + EyeRotation.Vector() * InteractDistance;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(SphereCastRadius);

	FHitResult Hit;
	//const bool bHasHit = World->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);
	const bool bHasHit = World->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape);

#if WITH_EDITOR
	static IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("dbga.DebugDraw.Enable"));
	const bool bEnabledDebug = CVar && CVar->GetBool();
	const FColor DebugColor = bHasHit ? FColor::Green : FColor::Red;

	if (bEnabledDebug)
	{
		DrawDebugLine(World, Start, End, DebugColor, false, 5.0f, 0, 2.0f);
	}
#endif // WITH_EDITOR


	if (bHasHit)
	{
#if WITH_EDITOR
		if (bEnabledDebug)
		{
			DrawDebugSphere(World, Hit.ImpactPoint, SphereCastRadius, 12, DebugColor, false, 5.0f, 0, 2.0f);
		}
#endif // WITH_EDITOR

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			const bool bHasGameplayInterface = HitActor->Implements<USGameplayInterface>();
			if (bHasGameplayInterface)
			{
				ISGameplayInterface::Execute_OnInteract(HitActor, OwnerActor);
			}
		}
	}
}