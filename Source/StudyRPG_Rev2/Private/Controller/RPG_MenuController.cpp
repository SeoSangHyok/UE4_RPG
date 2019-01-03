// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_MenuController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Character/RPG_BaseCharacter.h"
#include "UI/MainMenuWindow.h"
#include "UI/RPG_HUD.h"
#include "UI/CharacterSelectElem.h"
#include "GameMode/RPGGameInstance.h"
#include "GameMode/RPG_MenuGameState.h"
#include "UI/SelectWindow.h"


void ARPG_MenuController::BeginPlay()
{
	Super::BeginPlay();

	AActor* ViewTargetCameraActor = nullptr;

	for (TActorIterator<ACameraActor> It(GetWorld(), ACameraActor::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->GetName() == TEXT("MenuMainCamera"))
		{
			ViewTargetCameraActor = Actor;
			break;
		}
	}

	if (ViewTargetCameraActor)
	{
		SetViewTarget(ViewTargetCameraActor);
	}

	for (TActorIterator<ARPG_BaseCharacter> It(GetWorld(), ARPG_BaseCharacter::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->GetName() == TEXT("PreviewModel"))
		{
			PreviewCharacter = Actor;
			break;
		}
	}

	if (PreviewCharacter)
	{
		PreviewCharacter->SetActorHiddenInGame(true);
	}


	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());
	if (RPGGameInstance)
	{
		if (RPGGameInstance->FromGamePlay)
		{
			ARPG_MenuGameState* RPG_MenuGameState = Cast<ARPG_MenuGameState>(GetWorld()->GetGameState());
			if (RPG_MenuGameState)
				RPG_MenuGameState->MenuState = EGameMenuState::Select;

			ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(GetHUD());
			RPG_HUD->OpenWindowNew<USelectWindow>();
		}
		else
		{
			ARPG_MenuGameState* RPG_MenuGameState = Cast<ARPG_MenuGameState>(GetWorld()->GetGameState());
			if (RPG_MenuGameState)
				RPG_MenuGameState->MenuState = EGameMenuState::MainMenu;

			ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(GetHUD());
			RPG_HUD->OpenWindowNew<UMainMenuWindow>();
		}
	}

	bShowMouseCursor = true;
}

void ARPG_MenuController::SetPreviewCharacter(int32 CharacterTableId)
{
	if (PreviewCharacter)
	{
		ARPG_BaseCharacter* RPG_BaseCharacter = Cast<ARPG_BaseCharacter>(PreviewCharacter);
		if (RPG_BaseCharacter)
		{
			RPG_BaseCharacter->LoadSkeletalMeshByTable(CharacterTableId);
		}
	}
}