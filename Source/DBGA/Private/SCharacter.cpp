// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAnimInstance.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SAreaSpell.h"
#include "SGravitySpell.h"
#include "SAttributeComponent.h"
#include "SWeapon.h"


static TAutoConsoleVariable<bool> CVarEnableDebug(
	TEXT("dbga.DebugDraw.Enable"),
	false,
	TEXT("If true enable debug, false otherwise"),
	ECVF_Default
);


static TAutoConsoleVariable<float> CVarDebugDrawScale(
	TEXT("dbga.DebugDraw.DrawScale"),
	100.0f,
	TEXT("Size of the drawscale"),
	ECVF_Default
);

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>(TEXT("Interaction Component"));
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComponent"));
	
	WeaponComponent = CreateDefaultSubobject<ASWeapon>(TEXT("ASWeapon"));
	//WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	
	
	// USpringArmComponent
	CameraBoom->bUsePawnControlRotation = true;

	// dal ACharacter
	bUseControllerRotationYaw = false;

	// dal character movement component
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CurrentSpellIndex = 0;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	USAnimInstance* AnimInstance = Cast<USAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ASCharacter::OnNotifyBegin);
	}

	SetCurrentSpellIndex(0);

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
	AttributeComponent->OnManaChanged.AddDynamic(this, &ASCharacter::OnManaChanged);

	OnTakeRadialDamage.AddDynamic(this, &ASCharacter::OnRadialDamage);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	if (WeaponComponent)
	{
		WeaponComponent->Attach(this);
		UE_LOG(LogTemp, Warning, TEXT("ATTACHED?"));
	}
	/*
	ASWeapon* Weapon = GetWorld()->SpawnActor<ASWeapon>(ASWeapon::StaticClass(), SpawnParams);
	if (Weapon)
	{
		if (GetMesh()->DoesSocketExist("hand_r_spell_socket"))
		{
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("hand_r_spell_socket")));
			WeaponComponent = Weapon;
		}
	}
	*/

}


void ASCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	USAnimInstance* AnimInstance = Cast<USAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveAll(this);
	}

	AttributeComponent->OnHealthChanged.RemoveAll(this);
	AttributeComponent->OnManaChanged.RemoveAll(this);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpellClass)
	{
		const ASSpell* SpellCDO = SpellClass->GetDefaultObject<ASSpell>();

		if (SpellCDO && SpellCDO->GetSpellType() == ESpellType::AreaOfEffect)
		{
			const ASAreaSpell* AreaSpellCDO = Cast<ASAreaSpell>(SpellCDO);

			if (AreaSpellCDO)
			{
				UpdateSupportingSpellDecal(AreaSpellCDO->GetSpellDistance(), AreaSpellCDO->GetSpellRadius(), AreaSpellCDO->GetDecalComponentMaterial());
			}
		}
	}

#if WITH_EDITOR

	const bool bEnabledDebug = CVarEnableDebug.GetValueOnGameThread();

	if (bEnabledDebug)
	{
		UWorld* World = GetWorld();
		if (!World)
		{
			return;
		}

		const float DebugDrawScale = CVarDebugDrawScale.GetValueOnGameThread();
		const float DebugDrawArrowSize = 5.0f;

		const FVector LineStart = GetActorLocation() + (GetActorRightVector() * DebugDrawScale);
		const FVector LineEndActor = LineStart + (GetActorForwardVector() * DebugDrawScale);
		const FVector LineEndController = LineStart + (GetControlRotation().Vector() * DebugDrawScale);

		DrawDebugDirectionalArrow(World, LineStart, LineEndActor, DebugDrawScale, FColor::Yellow, false, 0.0f, 0, DebugDrawArrowSize);
		DrawDebugDirectionalArrow(World, LineStart, LineEndController, DebugDrawScale, FColor::Blue, false, 0.0f, 0, DebugDrawArrowSize);

	}

#endif // WITH_EDITOR

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASCharacter::OnInteract()
{
	InteractionComponent->OnInteract();
}

void ASCharacter::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	static const FName Cast_Begin = "Cast_Begin";
	static const FName Cast_Shoot = "Cast_Shoot";
	static const FName Cast_Ended = "Cast_Ended";

	if (NotifyName == Cast_Shoot)
	{
		OnAttack();
	}
}

void ASCharacter::OnAttack()
{
	UWorld* World = GetWorld();
	check(World);

	static const FName SpellSocket = "hand_r_spell_socket";

	const FVector SpawnLocation = GetMesh()->GetSocketLocation(SpellSocket);
	const FRotator SpawnRotationn = GetControlRotation();

	const FTransform SpawnTM = FTransform(SpawnRotationn, SpawnLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	World->SpawnActor<ASSpell>(SpellClass, SpawnTM, SpawnParams);
}

void ASCharacter::UpdateSupportingSpellDecal(float SpellDistance, float SpellRadius, UMaterialInterface* DecalComponentMaterial)
{
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);


	const FVector Start = EyeLocation;
	const FVector End = EyeLocation + EyeRotation.Vector() * SpellDistance;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FHitResult Hit;
	const bool bHasHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	if (bHasHit)
	{
		if (!SupportingSpellDecalComponent)
		{
			SupportingSpellDecalComponent = UGameplayStatics::SpawnDecalAtLocation(
				this,
				DecalComponentMaterial,
				FVector(SpellRadius, SpellRadius, SpellRadius),
				Hit.ImpactPoint
			);
		}
		else
		{
			SupportingSpellDecalComponent->SetWorldLocation(Hit.ImpactPoint);
		}
	}
	else
	{
		if (SupportingSpellDecalComponent)
		{
			SupportingSpellDecalComponent->DestroyComponent();
			SupportingSpellDecalComponent = nullptr;
		}
	}
}

void ASCharacter::SetCurrentSpellIndex(int32 NewSpellIndex)
{
	if (NewSpellIndex < 0 || NewSpellIndex >= SpellClasses.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid spell index: %d"), NewSpellIndex);
		return;
	}

	if (SpellClass)
	{
		const ASSpell* SpellCDO = SpellClass->GetDefaultObject<ASSpell>();
		if (SpellCDO && SpellCDO->GetSpellType() == ESpellType::AreaOfEffect)
		{
			if (SupportingSpellDecalComponent)
			{
				SupportingSpellDecalComponent->DestroyComponent();
				SupportingSpellDecalComponent = nullptr;
			}
		}
	}

	CurrentSpellIndex = NewSpellIndex;
	SpellClass = SpellClasses[CurrentSpellIndex];
}

int32 ASCharacter::GetCurrentSpellIndex()
{
	return CurrentSpellIndex;
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewValue, float DeltaValue)
{
#if WITH_EDITOR
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Instigator: %s, New Health: %f, Delta Health: %f"), *InstigatorActor->GetName(), NewValue, DeltaValue);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, DebugMessage);
	}
#endif // WITH_EDITOR
}

void ASCharacter::OnManaChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewValue, float DeltaValue)
{

#if WITH_EDITOR
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("New Mana: %f"), NewValue);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, DebugMessage);
	}
#endif // WITH_EDITOR
}

void ASCharacter::OnRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser)
{
	AttributeComponent->ApplyHealthChange(DamageCauser, Damage);
}