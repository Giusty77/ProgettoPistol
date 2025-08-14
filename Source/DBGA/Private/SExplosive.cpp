// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosive.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASExplosive::ASExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExplosiveMesh"));
	RootComponent = ExplosiveMesh;

	ExplosiveRadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplosiveRadialForceComponent"));
	ExplosiveRadialForceComponent->SetupAttachment(ExplosiveMesh);

	ExplosiveMesh->SetSimulatePhysics(true);

	ExplosiveRadialForceComponent->Radius = 500.0f;
	ExplosiveRadialForceComponent->ImpulseStrength = 200000.0f;

	ExplosiveMesh->SetCollisionProfileName("PhysicsActor");
}

// Called when the game starts or when spawned
void ASExplosive::BeginPlay()
{
	Super::BeginPlay();
	
	ExplosiveMesh->OnComponentHit.AddDynamic(this, &ASExplosive::OnHit);
}

// Called every frame
void ASExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosive::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || !OtherComp || OtherActor == this)
	{
		return;
	}

	// is ok if any pawn touch it! Must not explode at touch!
	if (OtherActor->IsA(APawn::StaticClass()))
	{
		return;
	}

	// Check if the hit actor is not the explosive itself
	if (OtherActor != this)
	{
		// Apply the radial force
		ExplosiveRadialForceComponent->FireImpulse();
		
		const FVector ImpulseDirection = Hit.Normal;
		const FVector AdditionalImpulse = ImpulseDirection * ExplosiveRadialForceComponent->Radius;

		ExplosiveMesh->AddImpulse(AdditionalImpulse, NAME_None, true);

		UGameplayStatics::ApplyRadialDamage(
			this,
			-25.0f,
			GetActorLocation(),
			ExplosiveRadialForceComponent->Radius,
			UDamageType::StaticClass(),
			TArray<AActor*>(),
			this,
			GetInstigatorController(),
			true);
	}
}

