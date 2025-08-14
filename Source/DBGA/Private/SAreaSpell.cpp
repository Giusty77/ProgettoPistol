// Fill out your copyright notice in the Description page of Project Settings.


#include "SAreaSpell.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASAreaSpell::ASAreaSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpellDistance = 10000.0f;
	SpellRadius = 100.0f;

	SpellType = ESpellType::AreaOfEffect;
}

// Called when the game starts or when spawned
void ASAreaSpell::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	check(World);

	AActor* OwnerActor = GetInstigator();

	FVector EyeLocation;
	FRotator EyeRotation;
	OwnerActor->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector Start = EyeLocation;
	const FVector End = EyeLocation + EyeRotation.Vector() * SpellDistance;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FHitResult Hit;
	const bool bHasHit = World->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);
	
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
			DrawDebugSphere(World, Hit.ImpactPoint, 50.0f, 12, DebugColor, false, 5.0f, 0, 2.0f);
		}
#endif // WITH_EDITOR

		BindSpellCollisionComponent();

		SpellCollisionComponent->SetSphereRadius(SpellRadius);
		SpellCollisionComponent->SetWorldLocation(Hit.ImpactPoint);

		NiagaraEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			NiagaraSystem,
			Hit.ImpactPoint,
			FRotator::ZeroRotator,
			FVector(1.0f),
			false,//true,           // Auto destroy?
			true,           // Auto activate
			ENCPoolMethod::None,
			true            // PreCullCheck
		);
	}
}

void ASAreaSpell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnbindSpellCollisionComponent();
}
