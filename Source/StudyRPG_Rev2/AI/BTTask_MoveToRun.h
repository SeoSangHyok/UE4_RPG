// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToRun.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UBTTask_MoveToRun : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	
public:
	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

public:
	UPROPERTY()
	float OriginSpeed;

	UPROPERTY(EditAnywhere)
	float SpeedScaleRate;
};
