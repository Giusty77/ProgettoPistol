// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "MySkeletalMeshComponent.generated.h"
//class ASCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DBGA_API UMySkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//bool AttachWeapon(ASCharacter* TargetCharacter);

	
public:
	// The Character holding this weapon
	//ASCharacter* Character;

	
};
