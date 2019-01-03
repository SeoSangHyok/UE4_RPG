// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_JumpEnd.h"
#include "Character/RPG_BaseCharacter.h"



void UAnimNotify_JumpEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPG_BaseCharacter* Rpg_BaseCharacter = Cast<ARPG_BaseCharacter>(MeshComp->GetOwner());

}