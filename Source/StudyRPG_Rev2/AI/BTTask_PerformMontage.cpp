// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_PerformMontage.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Animation/AnimMontage.h"
#include "Character/RPG_BaseEnemy_Rev2.h"


UBTTask_PerformMontage::UBTTask_PerformMontage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_PerformMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (!IsValid(RPG_BaseEnemy))
	{
		return EBTNodeResult::Type::Aborted;
	}

	if (nullptr == TargetMontage)
	{
		return EBTNodeResult::Type::Succeeded;
	}

	RPG_BaseEnemy->PlayAnimMontage(TargetMontage);

	return EBTNodeResult::Type::InProgress;

/*
	UWorld* World = RPG_BaseEnemy->GetWorld();
	if (nullptr == World)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Aborted);
		return;
	}

	ARPG_BaseCharacter* RPG_BaseCharacter = Cast<ARPG_BaseCharacter>(URpgGamePlayStatics::GetPlayerController(World, 0)->GetPawn());
	if (nullptr == RPG_BaseCharacter)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Aborted);
		return;
	}


*/
}

void UBTTask_PerformMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (!IsValid(RPG_BaseEnemy))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Aborted);
		return;
	}

	if (RPG_BaseEnemy->GetCurrentMontage() == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		return;
	}
}