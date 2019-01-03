// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_InputFlag.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UAnimNotify_InputFlag : public UAnimNotify
{
	GENERATED_BODY()
	
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimNotify_InputFlag", meta = (AllowPrivateAccess = "true"))
	bool Move;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimNotify_InputFlag", meta = (AllowPrivateAccess = "true"))
	bool Jump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimNotify_InputFlag", meta = (AllowPrivateAccess = "true"))
	bool Attack;
};
