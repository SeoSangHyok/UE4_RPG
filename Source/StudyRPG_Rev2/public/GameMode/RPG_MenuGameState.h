// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RPG_MenuGameState.generated.h"

UENUM()
enum class EGameMenuState : uint8
{
	MainMenu,
	Select
};

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARPG_MenuGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EGameMenuState MenuState;
	
};
