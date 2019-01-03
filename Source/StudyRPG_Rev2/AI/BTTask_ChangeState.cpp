// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ChangeState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"



EBTNodeResult::Type UBTTask_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BlackboardComponent->SetValueAsEnum(BlackBoardKey.SelectedKeyName, (uint8)State);

	return EBTNodeResult::Type::Succeeded;
}