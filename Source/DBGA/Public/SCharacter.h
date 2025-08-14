// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSpell.h"

#include "SCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UMaterialInterface;
class USAttributeComponent;
class USkeletalMeshComponent;
class ASWeapon;
class UMySkeletalMeshComponent;
	
UCLASS()
class DBGA_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBGA|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom; // Camera boom positioning the camera behind the character

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBGA|Camera")
	TObjectPtr<UCameraComponent> FollowCamera; // Follow camera

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBGA|Interaction")
	TObjectPtr<USInteractionComponent> InteractionComponent; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBGA|Attributes")
	TObjectPtr<USAttributeComponent> AttributeComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "DBGA|Character")
	void OnInteract();

	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION(BlueprintCallable, Category = "DBGA|Character")
	void SetCurrentSpellIndex(int32 NewSpellIndex);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Animation")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DBGA|Spell")
	TArray<TSubclassOf<ASSpell>> SpellClasses;

private:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewValue, float DeltaValue);

	UFUNCTION()
	void OnManaChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewValue, float DeltaValue);

	UFUNCTION()
	void OnRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

private: 
	UPROPERTY();
	TSubclassOf<ASSpell> SpellClass;

	

private:
	void OnAttack();
	void UpdateSupportingSpellDecal(float SpellDistance, float SpellRadius, UMaterialInterface* DecalComponentMaterial);

public:
	bool bIsBlocking;

private:
	TObjectPtr<UDecalComponent> SupportingSpellDecalComponent;
	int32 CurrentSpellIndex;



/*public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool AttachWeapon();
	*/
public:
	/*UPROPERTY();
	TSubclassOf<ASWeapon> WeaponClass;
	*/
	//UPROPERTY(EditDefaultsOnly, Category = "DBGA|weapon")
	//TObjectPtr<UMySkeletalMeshComponent> MeshGun;
	UPROPERTY();
	TSubclassOf<ASWeapon> WeaponClass;

	UPROPERTY()
	TObjectPtr<ASWeapon> Weapon;

	

	
};
