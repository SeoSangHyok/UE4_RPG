// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_PlayGameState.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Engine/World.h"
#include "Controller/Rpg_BaseController.h"
#include "UI/RPG_HUD.h"
#include "UI/MissionCompleteWindow.h"
#include "GameMode/RPGGameInstance.h"
#include "RpgSaveGame.h"
#include "EngineUtils.h"
#include "Character/RPG_BaseEnemy_Rev2.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BrainComponent.h"

void ARPG_PlayGameState::BeginPlay()
{
	Super::BeginPlay();

	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());
	if (RPGGameInstance)
	{
		TargetMonsterID = RPGGameInstance->TargetMonsterID;
	}
}


void ARPG_PlayGameState::MonsterDead(int32 MonsterID)
{
	if (TargetMonsterID == MonsterID)
	{
		ARpg_BaseController* Rpg_BaseController = URpgGamePlayStatics::GetRpgBaseController(GetWorld(), 0);

		if (Rpg_BaseController)
		{
			ClearDungeon = true;
			UpdateSaveData();

			ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(Rpg_BaseController->GetHUD());
			if (RPG_HUD)
			{
				UMissionCompleteWindow* MissionCompleteWindow = RPG_HUD->OpenWindowNew<UMissionCompleteWindow>();
				if (MissionCompleteWindow)
				{
					MissionCompleteWindow->SetCompleteText(TEXT("Dungeon Clear!!!"));
				}
			}
		}

		TSubclassOf<AActor> ActorClass;
		ActorClass = ARPG_BaseEnemy_Rev2::StaticClass();

		TArray<AActor> OutActors;

		UWorld* World = GetWorld();

		for (TActorIterator<AActor> It(World, ActorClass); It; ++It)
		{
			AActor* Actor = *It;
			ARPG_BaseEnemy_Rev2* RPG_BaseEnemy = Cast<ARPG_BaseEnemy_Rev2>(Actor);
			AAIController* AIController = Cast<AAIController>(RPG_BaseEnemy->GetController());
			if (AIController)
			{
				AIController->BrainComponent->StopLogic(TEXT("DungeonClear"));
			}
		}
	}
}

void ARPG_PlayGameState::PlayerDead()
{
	ARpg_BaseController* Rpg_BaseController = URpgGamePlayStatics::GetRpgBaseController(GetWorld(), 0);

	if (Rpg_BaseController)
	{
		UpdateSaveData();

		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(Rpg_BaseController->GetHUD());
		if (RPG_HUD)
		{
			UMissionCompleteWindow* MissionCompleteWindow = RPG_HUD->OpenWindowNew<UMissionCompleteWindow>();
			if (MissionCompleteWindow)
			{
				MissionCompleteWindow->SetCompleteText(TEXT("You Die..."));
			}			
		}
	}
}

void ARPG_PlayGameState::UpdateSaveData()
{
	if (UGameplayStatics::DoesSaveGameExist(URpgSaveGame::SaveSlotName(), 0))
	{
		URpgSaveGame* RpgSaveGame = Cast<URpgSaveGame>(UGameplayStatics::LoadGameFromSlot(URpgSaveGame::SaveSlotName(), 0));
		if (RpgSaveGame)
		{
			RpgSaveGame->ClearCount += ClearDungeon ? 1 : 0;
			RpgSaveGame->DieCount += ClearDungeon ? 0 : 1;
			RpgSaveGame->TotalDamageToEnemy += DamageToEnemy;
			RpgSaveGame->TotalDamageFromEnemy += DamageFromEnemy;

			UGameplayStatics::SaveGameToSlot(RpgSaveGame, URpgSaveGame::SaveSlotName(), 0);
		}
	}
	else
	{
		URpgSaveGame* RpgSaveGame = Cast<URpgSaveGame>(UGameplayStatics::CreateSaveGameObject(URpgSaveGame::StaticClass()));
		RpgSaveGame->InitData();

		RpgSaveGame->ClearCount += ClearDungeon ? 1 : 0;
		RpgSaveGame->DieCount += ClearDungeon ? 0 : 1;
		RpgSaveGame->TotalDamageToEnemy += DamageToEnemy;
		RpgSaveGame->TotalDamageFromEnemy += DamageFromEnemy;

		UGameplayStatics::SaveGameToSlot(RpgSaveGame, URpgSaveGame::SaveSlotName(), 0);
	}	
}