// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeSpeedRate.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UBTTask_ChangeSpeedRate : public UBTTaskNode
{
	GENERATED_BODY()
	
	
public:
	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}
	
};
