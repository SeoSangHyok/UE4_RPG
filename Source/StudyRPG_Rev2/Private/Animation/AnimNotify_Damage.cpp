// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_Damage.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "Character/RPG_BaseCharacter.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"



void UAnimNotify_Damage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UWorld* World = MeshComp->GetWorld();

	TArray<FOverlapResult> TestResult;

	FTransform Transform(FRotator::ZeroRotator, CenterPosition);
	Transform *= MeshComp->GetComponentTransform();

	FCollisionObjectQueryParams CollisionObjectQueryParams;
	if (FCollisionObjectQueryParams::IsValidObjectQuery(ECollisionChannel::ECC_Pawn))
	{
		CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	}
	
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(Radius);

	float Damage = 0.0f;
	ARPG_BaseEnemy_Rev2* RPG_BaseEnemy_Rev2 = Cast<ARPG_BaseEnemy_Rev2>(MeshComp->GetOwner());
	if (RPG_BaseEnemy_Rev2)
	{
		Damage = RPG_BaseEnemy_Rev2->CurrentUsingSkill->Damage;
	}

	ARPG_BaseCharacter* RPG_BaseCharacter = Cast<ARPG_BaseCharacter>(MeshComp->GetOwner());
	if (RPG_BaseCharacter)
	{
		Damage = RPG_BaseCharacter->CurrentUsingSkill->Damage;
	}

	World->OverlapMultiByObjectType(TestResult, Transform.GetLocation(), FRotator::ZeroRotator.Quaternion(), CollisionObjectQueryParams, CollisionShape);
	for (const FOverlapResult& OverlapResult : TestResult)
	{
		if (OverlapResult.Actor == MeshComp->GetOwner())
			continue;

		if (RPG_BaseEnemy_Rev2)
		{
			if (OverlapResult.Actor->IsA<ARPG_BaseCharacter>())
			{
				FDamageEvent DamageEvent;
				DamageEvent.DamageTypeClass = UDamageType::StaticClass();
				OverlapResult.Actor->TakeDamage(Damage,DamageEvent, RPG_BaseEnemy_Rev2->GetController(), NULL);
			}
		}
		else if (RPG_BaseCharacter)
		{
			if (OverlapResult.Actor->IsA<ARPG_BaseEnemy_Rev2>())
			{
				FDamageEvent DamageEvent;
				DamageEvent.DamageTypeClass = UDamageType::StaticClass();
				OverlapResult.Actor->TakeDamage(Damage, DamageEvent, RPG_BaseCharacter->GetController(), NULL);
			}
		}
	}

	if (ShowDebugInfo)
	{
		DrawDebugSphere(MeshComp->GetWorld(), Transform.GetLocation(), Radius, 16, FColor::Red, true, 1.0f, 0, 1.0f);
	}


}