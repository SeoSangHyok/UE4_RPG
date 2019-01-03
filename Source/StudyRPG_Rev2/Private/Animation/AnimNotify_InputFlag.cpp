// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_InputFlag.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/RPG_BaseCharacter.h"



void UAnimNotify_InputFlag::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPG_BaseCharacter* Rpg_BaseCharacter = Cast<ARPG_BaseCharacter>(MeshComp->GetOwner());
	if (IsValid(Rpg_BaseCharacter))
	{
		FInputFlag InputFlag;
		InputFlag.Move = Move;
		InputFlag.Jump = Jump;
		InputFlag.Attack = Attack;
		Rpg_BaseCharacter->SetInputFlag(InputFlag);
	}
}