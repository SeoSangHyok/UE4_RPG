// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_PlayGameMode.h"
#include "RPG_BaseCharacter.h"
#include "Rpg_BaseController.h"
#include "UI/RPG_HUD.h"
#include "RPG_PlayGameState.h"




ARPG_PlayGameMode::ARPG_PlayGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	DefaultPawnClass = ARPG_BaseCharacter::StaticClass();
	PlayerControllerClass = ARpg_BaseController::StaticClass();
	GameStateClass = ARPG_PlayGameState::StaticClass();
	HUDClass = ARPG_HUD::StaticClass();
}

