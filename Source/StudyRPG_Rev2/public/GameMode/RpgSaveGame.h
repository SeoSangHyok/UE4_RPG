// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RpgSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URpgSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	static FString SaveSlotName() { return TEXT("SaveGameData"); }

	void InitData();

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 ClearCount;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 DieCount;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 TotalDamageToEnemy;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 TotalDamageFromEnemy;
};
