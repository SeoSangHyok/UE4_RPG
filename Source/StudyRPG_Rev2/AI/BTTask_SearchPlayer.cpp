// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SearchPlayer.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Character/RPG_BaseCharacter.h"
#include "Engine/World.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SearchPlayer::UBTTask_SearchPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_SearchPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_SearchPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (!IsValid(RPG_BaseEnemy))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Aborted);
		return;
	}

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

	FVector Dist = RPG_BaseEnemy->GetActorLocation() - RPG_BaseCharacter->GetActorLocation();
	if (Dist.Size() <= RPG_BaseEnemy->GetSightRange())
	{
		TArray<AActor*> TraceIgnoreActors;
		TraceIgnoreActors.Add(RPG_BaseEnemy);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQuerys;
		ObjectQuerys.Add(EObjectTypeQuery::ObjectTypeQuery3);

		FHitResult HitResult;
		UKismetSystemLibrary::LineTraceSingleForObjects(
			World,
			RPG_BaseEnemy->GetActorLocation(),
			RPG_BaseCharacter->GetActorLocation(),
			ObjectQuerys,
			false,
			TraceIgnoreActors,
			EDrawDebugTrace::Type::ForOneFrame,
			HitResult,
			true
		);

		if (HitResult.bBlockingHit)
		{
			if (IsValid(Cast<ARPG_BaseCharacter>(HitResult.GetActor())))
			{
				UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
				BlackboardComponent->SetValueAsObject(TEXT("Target"), HitResult.GetActor());

//				BlackboardComponent->SetValueAsEnum(TEXT("State"), (uint8)EEnemyState::Chase);
				FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
				return;
			}
		}
	}
}