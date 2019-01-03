// Fill out your copyright notice in the Description page of Project Settings.

#include "EQSC_Player.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EngineUtils.h"
#include "Character/RPG_BaseCharacter.h"



void UEQSC_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	check(GetOuter() != NULL);

	UEnvQueryManager* EnvQueryManager = Cast<UEnvQueryManager>(GetOuter());
	if (EnvQueryManager != NULL)
	{
		UWorld* World = EnvQueryManager->GetWorld();

		TArray<AActor*> Actors;
		for (TActorIterator<AActor> It(World, ARPG_BaseCharacter::StaticClass()); It; ++It)
		{
			AActor* Actor = *It;

			if (!Actor->IsPendingKill())
			{
				Actors.Add(Actor);
			}
		}

		UEnvQueryItemType_Actor::SetContextHelper(ContextData, Actors);
	}
}