// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PerformMontage.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UBTTask_PerformMontage : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTTask_PerformMontage(const FObjectInitializer& ObjectInitializer);

	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	/** ticks this task
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

public:
	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BTTask_PerformMontage")
	class UAnimMontage* TargetMontage;

};
