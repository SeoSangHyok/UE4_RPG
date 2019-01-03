// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetHomeLoc.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UBTTaskNode_SetHomeLoc : public UBTTaskNode
{
	GENERATED_BODY()
	
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BTTaskNode_SetHomeLoc")
	FBlackboardKeySelector HomeLocationKey;
};
