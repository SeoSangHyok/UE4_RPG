// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPG_MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARPG_MenuGameMode : public AGameModeBase
{
	GENERATED_BODY()


	ARPG_MenuGameMode(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
