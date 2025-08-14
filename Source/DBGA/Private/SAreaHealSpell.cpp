// Fill out your copyright notice in the Description page of Project Settings.


#include "SAreaHealSpell.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASAreaHealSpell::ASAreaHealSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpellEffectPerSecond = 1.0f;
	TimeAccumulated = 0.0f;
}

void ASAreaHealSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeAccumulated += DeltaTime;

	if (TimeAccumulated >= SpellEffectPerSecond)
	{
		for (const AActor* OverlappedActor : OverlappedActors)
		{
#if WITH_EDITOR
			static IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("dbga.DebugDraw.Enable"));
			const bool bEnabledDebug = CVar && CVar->GetBool();

			if (bEnabledDebug)
			{
				if (GEngine)
				{
					FString DebugMessage = FString::Printf(TEXT("ASAreaHealSpell::Overlapped: %s"), *OverlappedActor->GetName());
					GEngine->AddOnScreenDebugMessage(INDEX_NONE, SpellEffectPerSecond, FColor::Green, DebugMessage);
				}
			}
#endif // WITH_EDITOR
		}

		TimeAccumulated -= SpellEffectPerSecond;
	}
}

void ASAreaHealSpell::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || !OtherComp)
	{
		return; // Ignore self and invalid actors
	}

	if (!OverlappedActors.Contains(OtherActor))
	{
		OverlappedActors.Add(OtherActor);
	}
}

void ASAreaHealSpell::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this || !OtherComp)
	{
		return; // Ignore self and invalid actors
	}

	if (OverlappedActors.Contains(OtherActor))
	{
		OverlappedActors.Remove(OtherActor);
	}
}

void ASAreaHealSpell::BindSpellCollisionComponent()
{
	SpellCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASAreaHealSpell::OnBeginOverlap);
	SpellCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASAreaHealSpell::OnEndOverlap);
}

void ASAreaHealSpell::UnbindSpellCollisionComponent()
{
	if (SpellCollisionComponent->OnComponentBeginOverlap.IsBound())
	{
		SpellCollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
	}

	if (SpellCollisionComponent->OnComponentEndOverlap.IsBound())
	{
		SpellCollisionComponent->OnComponentEndOverlap.RemoveAll(this);
	}
}