// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckDistByCurve.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

UBTService_CheckDistByCurve::UBTService_CheckDistByCurve(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UBTService_CheckDistByCurve::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	if (nullptr != TargetActor && nullptr != CurveBase)
	{
		FVector Dist = TargetActor->GetActorLocation() - AiOwner->GetActorLocation();

		float curveX = FMath::Clamp<float>(Dist.Size2D(), 0.0f, AiOwner->GetSightRange()) / AiOwner->GetSightRange();
		int ChageChance = CurveBase->GetFloatValue(curveX) * 1000;
		FString DebugMsg = FString::Printf(TEXT("Dist.Size2D() : %f, curveX : %f, ChageChance: %d"), Dist.Size2D(), curveX, ChageChance);
		GEngine->AddOnScreenDebugMessage((uint64)-1, 0.5, FColor::Red, DebugMsg);

		if ((FMath::Rand() % 1000) < ChageChance)
		{
			BlackboardComponent->SetValueAsEnum(StateKey.SelectedKeyName, (uint8)EEnemyState::Chase);
		}
	}
}

void UBTService_CheckDistByCurve::OnGameplayTaskInitialized(UGameplayTask& Task)
{
	Super::OnGameplayTaskInitialized(Task);
}

void UBTService_CheckDistByCurve::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTService_CheckDistByCurve::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}