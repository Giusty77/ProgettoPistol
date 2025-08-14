// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"


// Sets default values
ASWeapon::ASWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	MeshGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));

	
	/*
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));

	
	
	Mesh->GetStaticMesh();
	*/
	//WeaponComponents = CreateDefaultSubobject<UMySkeletalMeshComponent>(TEXT("WeaponComponent"));
	
	
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

