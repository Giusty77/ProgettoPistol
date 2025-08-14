// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportSpell.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTeleportSpell::ASTeleportSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpellMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SpellMovementComponent"));
	SpellMovementComponent->InitialSpeed = 1000.0f;
	SpellMovementComponent->bRotationFollowsVelocity = true;
	SpellMovementComponent->bInitialVelocityInLocalSpace = true;

	SpellMovementComponent->ProjectileGravityScale = 0.0f;

	SpellType = ESpellType::Projectile;
}


// Called when the game starts or when spawned
void ASTeleportSpell::BeginPlay()
{
	Super::BeginPlay();

	if (NiagaraSystem)
	{
		NiagaraEffectComponent->ActivateSystem();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NiagaraSystem is not set for ASSpell!"));
	}

	SpellCollisionComponent->OnComponentHit.AddDynamic(this, &ASTeleportSpell::OnHit);
}


void ASTeleportSpell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SpellCollisionComponent->OnComponentHit.RemoveAll(this);
}

void ASTeleportSpell::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SpellEnded(Hit.ImpactPoint);


#if WITH_EDITOR

	static IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("dbga.DebugDraw.Enable"));
	const bool bEnabledDebug = CVar && CVar->GetBool();

	if (bEnabledDebug)
	{
		if (GEngine)
		{
			FString DebugMessage = FString::Printf(TEXT("OnHit: %s"), *OtherActor->GetName());
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, DebugMessage);
		}
	}

#endif // WITH_EDITOR
}

void ASTeleportSpell::SpellEnded(FVector Location)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitNiagaraSystem, Location, GetActorRotation());

	GetInstigator()->TeleportTo(GetActorLocation(), GetActorRotation());

	Destroy();
}
