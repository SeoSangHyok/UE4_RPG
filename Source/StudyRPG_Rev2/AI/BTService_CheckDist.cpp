// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckDist.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_CheckDist::UBTService_CheckDist(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bNotifyOnSearch = true;
	
	bNotifyBecomeRelevant = true;

	bNotifyCeaseRelevant = true;

//	bNotifyTick = true;
}

void UBTService_CheckDist::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* AiOwner = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (nullptr == AiOwner)
		return;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (nullptr == BlackboardComponent)
		return;

	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (nullptr == TargetActor)
		return;

	CheckTime += DeltaSeconds;

	if (nullptr != TargetActor)
	{
		FVector Dist = TargetActor->GetActorLocation() - AiOwner->GetActorLocation();
		float BaseChance = 0.1f;
		if (Dist.Size2D() >= AiOwner->GetSightRange())
		{
			float ClampedDist = FMath::Clamp<float>(Dist.Size2D(), AiOwner->GetSightRange(), AiOwner->GetSightRange()*2);
			BaseChance = 0.1f + (ClampedDist / (AiOwner->GetSightRange() * 2)) * 0.5f;

			float ChanceWeight = 0.5f;
			if (CheckTime < 10.0f)
			{
				ChanceWeight = (CheckTime / (10.0f)) * 0.5f;
			}
			else if (10.0f <= CheckTime)
			{
				float ClampedTime = FMath::Clamp<float>(CheckTime, 10.0f, 20.0f);
				ChanceWeight = 0.5f + (ClampedTime / (20.0f)) * 0.5f;
			}

			int AbandonResult = (BaseChance * ChanceWeight) * 1000;
			if ((FMath::Rand() % 1000) < AbandonResult)
			{
				BlackboardComponent->SetValueAsEnum(StateKey.SelectedKeyName, (uint8)EEnemyState::Back);
			}
		}
	}
}

void UBTService_CheckDist::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	CheckTime = 0.0f;
}

void UBTService_CheckDist::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	CheckTime = 0.0f;
}

void UBTService_CheckDist::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	CheckTime = 0.0f;
}

void UBTService_CheckDist::OnGameplayTaskInitialized(UGameplayTask& Task) 
{
	Super::OnGameplayTaskInitialized(Task);

	dummyVal = 1;
}

void UBTService_CheckDist::OnGameplayTaskActivated(UGameplayTask& Task) 
{
	Super::OnGameplayTaskActivated(Task);

	dummyVal = 1;
}

void UBTService_CheckDist::OnGameplayTaskDeactivated(UGameplayTask& Task) 
{
	Super::OnGameplayTaskDeactivated(Task);

	dummyVal = 2;
}