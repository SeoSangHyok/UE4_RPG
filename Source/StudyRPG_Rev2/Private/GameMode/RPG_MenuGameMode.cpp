// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_MenuGameMode.h"
#include "Controller/RPG_MenuController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "GameMode/RPG_MenuGameState.h"
#include "UI/RPG_HUD.h"



ARPG_MenuGameMode::ARPG_MenuGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = APawn::StaticClass();
	PlayerControllerClass = ARPG_MenuController::StaticClass();
	GameStateClass = ARPG_MenuGameState::StaticClass();
	HUDClass = ARPG_HUD::StaticClass();
}


void ARPG_MenuGameMode::BeginPlay()
{
	Super::BeginPlay();


}