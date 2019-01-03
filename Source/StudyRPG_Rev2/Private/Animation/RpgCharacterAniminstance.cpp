// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgCharacterAniminstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void URpgCharacterAniminstance::PreUpdateAnimation(float DeltaSeconds)
{
	Super::PreUpdateAnimation(DeltaSeconds);

	ARPG_BaseCharacter* OwningRpgCharacter = GetOwnRpgBaseCharacter();
	if (!IsValid(OwningRpgCharacter))
		return;

	FVector Velocity = OwningRpgCharacter->GetVelocity();
	Speed = Velocity.Size2D();

	ECharacterState PrevCharacterState = CharacterState;
	CharacterState = OwningRpgCharacter->GetCharacterState();
	if (ECharacterState::Jump == CharacterState && ECharacterState::Jump != PrevCharacterState)
	{
		IsRunningJump = Velocity.Size2D() >= 100;
	}

	CurrentHP = OwningRpgCharacter->CurrentHP;
}

ARPG_BaseCharacter* URpgCharacterAniminstance::GetOwnRpgBaseCharacter()
{
	return Cast<ARPG_BaseCharacter>(GetOwningActor());
}