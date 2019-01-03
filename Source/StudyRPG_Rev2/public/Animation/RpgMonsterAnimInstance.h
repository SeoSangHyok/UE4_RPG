// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/RPG_BaseEnemy.h"
#include "RpgMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URpgMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void PreUpdateAnimation(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "URpgCharacterAniminstance")
	class ARPG_BaseEnemy_Rev2* GetOwnRpgBaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgMonsterAnimInstance")
	int DeathMotionIdx = 0;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgMonsterAnimInstance", meta = (AllowPrivateAccess = "true"))
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URpgMonsterAnimInstance", meta = (AllowPrivateAccess = "true"))
	float CurrentHP = 0.0f;
};
