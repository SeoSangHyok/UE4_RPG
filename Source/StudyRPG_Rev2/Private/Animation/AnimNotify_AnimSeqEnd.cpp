// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_AnimSeqEnd.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/RPG_BaseCharacter.h"



void UAnimNotify_AnimSeqEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPG_BaseCharacter* Rpg_BaseCharacter = Cast<ARPG_BaseCharacter>(MeshComp->GetOwner());
	if (IsValid(Rpg_BaseCharacter))
	{
		Rpg_BaseCharacter->OnAnimSequenceEnd(Animation);
	}
}