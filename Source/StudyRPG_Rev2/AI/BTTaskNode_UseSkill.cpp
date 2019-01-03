// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_UseSkill.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_UseSkill::UBTTaskNode_UseSkill(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_UseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ARPG_BaseEnemy_Rev2* AiOwner = Cast<ARPG_BaseEnemy_Rev2>(AIController->GetPawn());
	if (nullptr == AiOwner)
		return EBTNodeResult::Type::Aborted;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (nullptr == BlackboardComponent)
		return EBTNodeResult::Type::Aborted;

	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (nullptr == TargetActor)
		return EBTNodeResult::Type::Aborted;

	const FMonsterInfoTB* MonsterInfoTB = AiOwner->GetMonsterInfoTB();
	TArray<const FSkillInfoTB*> SkillList;
	const FSkillInfoTB* SkillInfoTB = URpgGamePlayStatics::FindTable<FSkillInfoTB>(MonsterInfoTB->Skill1);
	if (nullptr != SkillInfoTB)
		SkillList.Add(SkillInfoTB);

	SkillInfoTB = URpgGamePlayStatics::FindTable<FSkillInfoTB>(MonsterInfoTB->Skill2);
	if (nullptr != SkillInfoTB)
		SkillList.Add(SkillInfoTB);

	SkillInfoTB = URpgGamePlayStatics::FindTable<FSkillInfoTB>(MonsterInfoTB->Skill3);
	if (nullptr != SkillInfoTB)
		SkillList.Add(SkillInfoTB);

	if (SkillList.Num() == 0)
		return EBTNodeResult::Type::Aborted;

	int UseSkillIndex = FMath::Rand() % SkillList.Num();
	if (0 != SkillID)
	{
		UseSkillIndex = -1;

		for (int i = 0; i < SkillList.Num(); i++)
		{
			if (SkillList[i]->ID == SkillID)
			{
				UseSkillIndex = i;
				break;
			}
		}
	}

	if (-1 == UseSkillIndex)
		return EBTNodeResult::Type::Aborted;

	UAnimMontage* SkillMontage = Cast<UAnimMontage>(URpgGamePlayStatics::LoadObjectFromPath(UAnimMontage::StaticClass(), SkillList[UseSkillIndex]->AnimMontage));
	if (nullptr == SkillMontage)
		return EBTNodeResult::Type::Aborted;	

	FVector AiFwdVector = AiOwner->GetActorForwardVector();
	FVector TargetDirection = TargetActor->GetActorLocation() - AiOwner->GetActorLocation();
	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(AiFwdVector, TargetDirection);
	Rotator.Pitch = 0.0f;
	Rotator.Roll = 0.0f;
	AiOwner->SetActorRotation(Rotator);

	AiOwner->PlayAnimMontage(SkillMontage);
	AiOwner->CurrentUsingSkill = SkillList[UseSkillIndex];
	BlackboardComponent->SetValueAsFloat(SkillCoolTimeKey.SelectedKeyName, SkillList[UseSkillIndex]->CoolTime);

	return EBTNodeResult::Type::InProgress;
}

void UBTTaskNode_UseSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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