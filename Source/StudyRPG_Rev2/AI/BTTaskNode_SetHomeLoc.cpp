// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_SetHomeLoc.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"


EBTNodeResult::Type UBTTaskNode_SetHomeLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (nullptr == AIController)
		return EBTNodeResult::Type::Aborted;

	ARPG_BaseEnemy_Rev2* AIOwner = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (nullptr == AIOwner)
		return EBTNodeResult::Type::Aborted;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (nullptr == BlackboardComponent)
		return EBTNodeResult::Type::Aborted;

	BlackboardComponent->SetValueAsVector(HomeLocationKey.SelectedKeyName, AIOwner->GetHomePosition());

	return EBTNodeResult::Type::Succeeded;
}