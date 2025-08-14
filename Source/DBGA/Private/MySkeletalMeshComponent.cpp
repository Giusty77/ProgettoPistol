// Fill out your copyright notice in the Description page of Project Settings.


#include "MySkeletalMeshComponent.h"
#include "SCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
/*
bool UMySkeletalMeshComponent::AttachWeapon(ASCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	
	// Check that the character is valid, and has no weapon component yet
	if (Character == nullptr || Character->GetInstanceComponents().FindItemByClass<UMySkeletalMeshComponent>())
	{
		return false;
	}
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName(TEXT("hand_r_gun_socket")));
	return true;
}*/
