// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Damage.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UAnimNotify_Damage : public UAnimNotify
{
	GENERATED_BODY()
	
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", Meta = (MakeEditWidget = "true"))
	FVector CenterPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool ShowDebugInfo;
};
