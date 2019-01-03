// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckDist.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UBTService_CheckDist : public UBTService
{
	GENERATED_BODY()

	UBTService_CheckDist(const FObjectInitializer& ObjectInitializer);
	
protected:
	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** called when search enters underlying branch
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);

	/** called when auxiliary node becomes active
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	/** called when auxiliary node becomes inactive
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
	/** Notify called after GameplayTask finishes initialization (not active yet) */
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task);

	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task);

	/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task);

public:
	int32 dummyVal;

	float CheckTime;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BTService_CheckDist")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BTService_CheckDist")
	FBlackboardKeySelector StateKey;
};
