// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CheckRun.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"




EBTNodeResult::Type UBTTask_CheckRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (!IsValid(RPG_BaseEnemy))
	{
		return EBTNodeResult::Type::Aborted;
	}

	EEnemyState ResultState = RunFailState;

	if (CheckHpRate >= RPG_BaseEnemy->CurrentHP / RPG_BaseEnemy->GetMonsterInfoTB()->HP )
	{
		if (RunChance * 100 >= FMath::Rand() % 100)
		{
			ResultState = EEnemyState::Run;
		}
	}

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BlackboardComponent->SetValueAsEnum(StateBlackBoardKey.SelectedKeyName, (uint8)ResultState);

	return EBTNodeResult::Type::Succeeded;
}