// Fill out your copyright notice in the Description page of Project Settings.


#include "SGravitySpell.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"	
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


ASGravitySpell::ASGravitySpell()
{
	PrimaryActorTick.bCanEverTick = true;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);	

	SpellStrength = -1000000.0f;

	RadialForceComponent->Radius = SpellRadius * 10.0f;
	RadialForceComponent->ForceStrength = SpellStrength;
	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	SpellCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpellCollisionComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
}

void ASGravitySpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> ToRemove;

	for (auto& Elem : AffectedActors)
	{
		AActor* Target = Elem.Key;
		if (!IsValid(Target)) {
			ToRemove.Add(Target);
			continue;
		}

		FVector Direction = (GetActorLocation() - Target->GetActorLocation()).GetSafeNormal();
		UPrimitiveComponent* TargetComp = Cast<UPrimitiveComponent>(Target->GetRootComponent());
		if (TargetComp && TargetComp->IsSimulatingPhysics())
		{
			TargetComp->AddForce(Direction * 50000.f);
		}

		FVector CurrentScale = Target->GetActorScale3D();
		FVector NewScale = CurrentScale * (1.f - DeltaTime); // shrink over time
		NewScale.X = FMath::Max(NewScale.X, 0.05f);
		NewScale.Y = FMath::Max(NewScale.Y, 0.05f);
		NewScale.Z = FMath::Max(NewScale.Z, 0.05f);

		Target->SetActorScale3D(NewScale);

		if (NewScale.GetMin() <= 0.1f) // Threshold to explode!
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OverlapNiagaraSystem, Target->GetActorLocation());
			Target->Destroy();
			ToRemove.Add(Target);
		}
	}

	// Remove destroyed actors from tracking
	for (AActor* Dead : ToRemove)
	{
		AffectedActors.Remove(Dead);
	}
}

void ASGravitySpell::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || !OtherComp)
	{
		return; // Ignore self and invalid actors
	}

	if (OtherComp->IsSimulatingPhysics())
	{
		//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OverlapNiagaraSystem, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
		//OtherActor->Destroy(); // Destroy the actor if it has physics simulation enabled
		if (!AffectedActors.Contains(OtherActor))
		{
			AffectedActors.Add(OtherActor, 0.f);
		}
	}
}

void ASGravitySpell::BindSpellCollisionComponent()
{
	SpellCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGravitySpell::OnBeginOverlap);
}

void ASGravitySpell::UnbindSpellCollisionComponent()
{
	if (SpellCollisionComponent->OnComponentBeginOverlap.IsBound())
	{
		SpellCollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}