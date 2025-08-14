// Fill out your copyright notice in the Description page of Project Settings.


#include "SSpell.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

// Sets default values
ASSpell::ASSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpellCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SpellCollisionComponent"));
	RootComponent = SpellCollisionComponent;

	NiagaraEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffectComponent"));
	NiagaraEffectComponent->SetupAttachment(SpellCollisionComponent);
	NiagaraEffectComponent->SetAutoActivate(false); // Set to false to control activation manually
	NiagaraEffectComponent->bAutoActivate = false;

	SpellCollisionComponent->SetCollisionProfileName("Spell");
	SpellCollisionComponent->SetGenerateOverlapEvents(true);

	SpellDuration = 0.0f;	// does not expire!
}

// Called when the game starts or when spawned
void ASSpell::BeginPlay()
{
	Super::BeginPlay();

	if (NiagaraSystem)
	{
		NiagaraEffectComponent->SetAsset(NiagaraSystem);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NiagaraSystem is not set for ASSpell!"));
	}

	AActor* CurrentInstigator = GetInstigator();
	if (SpellCollisionComponent && CurrentInstigator)
	{
		SpellCollisionComponent->IgnoreActorWhenMoving(CurrentInstigator, true);
	}

	if (SpellDuration > 0.0f)
	{
		FTimerHandle SpellDurationTimer;
		GetWorld()->GetTimerManager().SetTimer(SpellDurationTimer, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				SpellEnded(GetActorLocation());
			}), SpellDuration, false);
	}
}


void ASSpell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ASSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASSpell::SpellEnded(FVector Location)
{
	NiagaraEffectComponent->Deactivate();
	Destroy();
}