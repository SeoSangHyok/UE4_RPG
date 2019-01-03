// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWindow.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Animation/WidgetAnimation.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/Slate/Public/Framework/SlateDelegates.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/RPG_MenuGameState.h"
#include "UI/RPG_HUD.h"
#include "UI/SelectWindow.h"
#include "Controller/RPG_MenuController.h"
#include "GameMode/RpgSaveGame.h"
#include "GameMode/RPGGameInstance.h"

UMainMenuWindow::UMainMenuWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WindowTableID = 1;
}

void UMainMenuWindow::AssignComponents()
{
	NewButton = Cast<UButton>(MainWidget->GetWidgetFromName(TEXT("NewButton")));
	NewButton->OnClicked.AddDynamic(this, &UMainMenuWindow::OnClick_NewButton);

	LoadButton = Cast<UButton>(MainWidget->GetWidgetFromName(TEXT("LoadButton")));
	LoadButton->OnClicked.AddDynamic(this, &UMainMenuWindow::OnClick_LoadButton);

	QuitButton = Cast<UButton>(MainWidget->GetWidgetFromName(TEXT("QuitButton")));
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWindow::OnClick_QuitButton);
}

void UMainMenuWindow::OnOpened()
{
	UWidgetAnimation** WidgetAnimation = WidgetAnimationList.Find(TEXT("ShowMenu"));
	if (WidgetAnimation)
	{
		MainWidget->PlayAnimation(*WidgetAnimation);
	}
}

void UMainMenuWindow::OnClick_NewButton()
{
	ARPG_MenuController* PlayerController = Cast<ARPG_MenuController>(MainWidget->GetOwningPlayer());
	ARPG_MenuGameState* RPG_MenuGameState = Cast<ARPG_MenuGameState>(PlayerController->GetWorld()->GetGameState());
	if (RPG_MenuGameState)
	{
		RPG_MenuGameState->MenuState = EGameMenuState::Select;

		if (UGameplayStatics::DoesSaveGameExist(URpgSaveGame::SaveSlotName(), 0))
		{
			URpgSaveGame* RpgSaveGame = Cast<URpgSaveGame>(UGameplayStatics::LoadGameFromSlot(URpgSaveGame::SaveSlotName(), 0));
			if (RpgSaveGame)
			{
				RpgSaveGame->InitData();
				UGameplayStatics::SaveGameToSlot(RpgSaveGame, URpgSaveGame::SaveSlotName(), 0);
			}
		}
		else
		{
			URpgSaveGame* RpgSaveGame = Cast<URpgSaveGame>(UGameplayStatics::CreateSaveGameObject(URpgSaveGame::StaticClass()));
			RpgSaveGame->InitData();
			UGameplayStatics::SaveGameToSlot(RpgSaveGame, URpgSaveGame::SaveSlotName(), 0);
		}

		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(PlayerController->GetHUD());
		RPG_HUD->OpenWindowNew<USelectWindow>();
	}
}

void UMainMenuWindow::OnClick_LoadButton()
{
	ARPG_MenuController* PlayerController = Cast<ARPG_MenuController>(MainWidget->GetOwningPlayer());
	ARPG_MenuGameState* RPG_MenuGameState = Cast<ARPG_MenuGameState>(PlayerController->GetWorld()->GetGameState());
	if (RPG_MenuGameState)
	{
		RPG_MenuGameState->MenuState = EGameMenuState::Select;

		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(PlayerController->GetHUD());
		RPG_HUD->OpenWindowNew<USelectWindow>();
	}
}

void UMainMenuWindow::OnClick_QuitButton()
{
	UKismetSystemLibrary::QuitGame(MainWidget->GetWorld(), MainWidget->GetOwningPlayer(), EQuitPreference::Quit, true);
}