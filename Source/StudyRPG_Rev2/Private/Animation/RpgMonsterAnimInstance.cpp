// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgMonsterAnimInstance.h"
#include "Character/RPG_BaseEnemy_Rev2.h"



void URpgMonsterAnimInstance::PreUpdateAnimation(float DeltaSeconds)
{
	Super::PreUpdateAnimation(DeltaSeconds);

	ARPG_BaseEnemy_Rev2* OwningRpgEnemy = GetOwnRpgBaseEnemy();
	if (!IsValid(OwningRpgEnemy))
		return;

	FVector Velocity = OwningRpgEnemy->GetVelocity();
	Speed = Velocity.Size2D();

	CurrentHP = OwningRpgEnemy->CurrentHP;
}

ARPG_BaseEnemy_Rev2* URpgMonsterAnimInstance::GetOwnRpgBaseEnemy()
{
	return Cast<ARPG_BaseEnemy_Rev2>(GetOwningActor());
}