// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/RPG_BaseCharacter.h"
#include "RpgCharacterAniminstance.generated.h"

/**
 * 
 */

UCLASS()
class STUDYRPG_REV2_API URpgCharacterAniminstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void PreUpdateAnimation(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "URpgCharacterAniminstance")
	ARPG_BaseCharacter* GetOwnRpgBaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgCharacterAniminstance")
	int DeathMotionIdx = 0;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgCharacterAniminstance", meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState = ECharacterState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgCharacterAniminstance", meta = (AllowPrivateAccess = "true"))
	float Speed = 0.0f;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgCharacterAniminstance", meta = (AllowPrivateAccess = "true"))
	bool IsRunningJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgCharacterAniminstance", meta = (AllowPrivateAccess = "true"))
	float CurrentHP = 0.0f;
};
