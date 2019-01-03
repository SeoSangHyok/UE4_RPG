// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RPG_PlayGameState.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARPG_PlayGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void MonsterDead(int32 MonsterID);
	void PlayerDead();

private:
	void UpdateSaveData();

public:
	UPROPERTY()
	int32 TargetMonsterID = 0;

	UPROPERTY()
	bool ClearDungeon = false;

	UPROPERTY()
	int32 DamageToEnemy = 0;

	UPROPERTY()
	int32 DamageFromEnemy = 0;
};
