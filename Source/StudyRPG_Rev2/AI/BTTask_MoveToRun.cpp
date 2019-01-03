// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToRun.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"



EBTNodeResult::Type UBTTask_MoveToRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Retval = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());

	OriginSpeed = RPG_BaseEnemy->GetCharacterMovement()->MaxWalkSpeed;
	RPG_BaseEnemy->GetCharacterMovement()->MaxWalkSpeed = OriginSpeed*SpeedScaleRate;

	return Retval;
}

void UBTTask_MoveToRun::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());

	RPG_BaseEnemy->GetCharacterMovement()->MaxWalkSpeed = OriginSpeed;
}