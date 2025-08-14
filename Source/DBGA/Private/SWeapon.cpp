// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"

#include "SCharacter.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	//WeaponMesh->SetVisibility(false);
	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASWeapon::ToggleVisibility()
{
	WeaponMesh->ToggleVisibility();
}

void ASWeapon::Attach(ASCharacter* Parent)
{
	this->WeaponMesh = Parent->WeaponMesh;
	TObjectPtr<USkeletalMeshComponent> ParentMesh = Parent->GetMesh();
	if (WeaponMesh && !WeaponMesh->IsAttachedTo(ParentMesh))
	{
		const FAttachmentTransformRules& AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		static const FName socketName("hand_r_spell_socket");
		bool socketFound = ParentMesh->DoesSocketExist("hand_r_spell_socket");
		UE_LOG(LogTemp, Warning, TEXT("Attached socket: %hs"), socketFound?"true":"false");
		bool result = WeaponMesh->AttachToComponent(ParentMesh, AttachmentRules, socketName);
		UE_LOG(LogTemp, Warning, TEXT("Attached Weapon: %hs"), result?"true":"false");
	} else 
		UE_LOG(LogTemp, Warning, TEXT("NOT ATTACHED"));
	
}
