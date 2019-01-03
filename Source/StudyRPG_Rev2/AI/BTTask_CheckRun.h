// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "BTTask_CheckRun.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UBTTask_CheckRun : public UBTTaskNode
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CheckRun", meta = (UIMin = 0, ClapmMin = 0, UIMax = 1, Const= 1))
	float CheckHpRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CheckRun", meta = (UIMin = 0, ClapmMin = 0, UIMax = 1, Const = 1))
	float RunChance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CheckRun")
	FBlackboardKeySelector StateBlackBoardKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CheckRun")
	EEnemyState RunFailState;
};
