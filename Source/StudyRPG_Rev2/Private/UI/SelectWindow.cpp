// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectWindow.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "GameMode/RPG_MenuGameState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "UI/RPG_HUD.h"
#include "UI/MainMenuWindow.h"
#include "Controller/RPG_MenuController.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Table/Rpg_TableDef.h"
#include "UI/CharacterSelectElem.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "UI/RpgScrollBox.h"
#include "GameMode/RPGGameInstance.h"
#include "GameMode/RpgSaveGame.h"


USelectWindow::USelectWindow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WindowTableID = 2;
}

void USelectWindow::AssignComponents()
{
	StartButton = Cast<UButton>(MainWidget->GetWidgetFromName(TEXT("StartButton")));
	StartButton->OnClicked.AddDynamic(this, &USelectWindow::OnClick_StartButton);

	BackButton = Cast<UButton>(MainWidget->GetWidgetFromName(TEXT("BackButton")));
	BackButton->OnClicked.AddDynamic(this, &USelectWindow::OnClick_BackButton);


	CharacterList = Cast<URpgScrollBox>(MainWidget->GetWidgetFromName(TEXT("CharacterList")));
	CharacterList->OnRpgScrollBoxSelectItem.AddDynamic(this, &USelectWindow::OnSelectedCharacter);

	MapList = Cast<URpgScrollBox>(MainWidget->GetWidgetFromName(TEXT("MapList")));
	MapList->OnRpgScrollBoxSelectItem.AddDynamic(this, &USelectWindow::OnSelectedMap);

	ClearCount = Cast<UTextBlock>(MainWidget->GetWidgetFromName(TEXT("ClearCount")));
	DieCount = Cast<UTextBlock>(MainWidget->GetWidgetFromName(TEXT("DieCount")));
	DamageToEnemy = Cast<UTextBlock>(MainWidget->GetWidgetFromName(TEXT("DamageToEnemy")));
	DamageFromEnemy = Cast<UTextBlock>(MainWidget->GetWidgetFromName(TEXT("DamageFromEnemy")));
}

void USelectWindow::OnOpened()
{
	ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(MainWidget->GetOwningPlayer()->GetHUD());

	TArray<FCharacterInfoTB*>  WindowInfoTbList;
	URpgGamePlayStatics::GetTableElemList<FCharacterInfoTB>(WindowInfoTbList);

	for (const FCharacterInfoTB* CharacterInfoTB : WindowInfoTbList)
	{
		UCharacterSelectElem* CharacterSelectElemWidget = RPG_HUD->CreateRpgWidget<UCharacterSelectElem>(MainWidget->GetOwningPlayer());

		UTexture2D* ThumbnailImage = Cast<UTexture2D>(URpgGamePlayStatics::LoadObjectFromPath(UTexture2D::StaticClass(), CharacterInfoTB->Thumbnail));
		CharacterSelectElemWidget->_Thumbnail->SetBrushFromTexture(ThumbnailImage);
		CharacterSelectElemWidget->_CharacterName->SetText(FText::FromString(CharacterInfoTB->CharacterName));
		CharacterSelectElemWidget->CharacterID = CharacterInfoTB->ID;

		CharacterList->AddChild(CharacterSelectElemWidget);
	}

	TArray<FMapInfoTB*>  MapInfoTbList;
	URpgGamePlayStatics::GetTableElemList<FMapInfoTB>(MapInfoTbList);

	for (const FMapInfoTB* MapInfoTB : MapInfoTbList)
	{
		UCharacterSelectElem* CharacterSelectElemWidget = RPG_HUD->CreateRpgWidget<UCharacterSelectElem>(MainWidget->GetOwningPlayer());

		UTexture2D* ThumbnailImage = Cast<UTexture2D>(URpgGamePlayStatics::LoadObjectFromPath(UTexture2D::StaticClass(), MapInfoTB->Thumbnail));
		CharacterSelectElemWidget->_Thumbnail->SetBrushFromTexture(ThumbnailImage);
		CharacterSelectElemWidget->_CharacterName->SetText(FText::FromString(MapInfoTB->MapName));
		CharacterSelectElemWidget->CharacterID = MapInfoTB->ID;

		MapList->AddChild(CharacterSelectElemWidget);
	}

	if (UGameplayStatics::DoesSaveGameExist(URpgSaveGame::SaveSlotName(), 0))
	{
		URpgSaveGame* RpgSaveGame = Cast<URpgSaveGame>(UGameplayStatics::LoadGameFromSlot(URpgSaveGame::SaveSlotName(), 0));
		if (RpgSaveGame)
		{
			ClearCount->SetText(FText::FromString(FString::FromInt(RpgSaveGame->ClearCount)));
			DieCount->SetText(FText::FromString(FString::FromInt(RpgSaveGame->DieCount)));
			DamageToEnemy->SetText(FText::FromString(FString::FromInt(RpgSaveGame->TotalDamageToEnemy)));
			DamageFromEnemy->SetText(FText::FromString(FString::FromInt(RpgSaveGame->TotalDamageFromEnemy)));
		}
	}
}

void USelectWindow::OnClick_StartButton()
{
	if (SelectedCharacterID == 0 || SelectedMapID == 0)
		return;

	ARPG_MenuController* PlayerController = Cast<ARPG_MenuController>(MainWidget->GetOwningPlayer());
	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(PlayerController->GetWorld()->GetGameInstance());
	if (RPGGameInstance)
	{
		RPGGameInstance->SelectedCharacterID = SelectedCharacterID;
		const FMapInfoTB* MapInfoTB = URpgGamePlayStatics::FindTable<FMapInfoTB>(SelectedMapID);
		RPGGameInstance->TargetMonsterID = MapInfoTB->TargetMonster;
	}

	URpgGamePlayStatics::LoadLevelUsingLevelTable(MainWidget->GetOwningPlayer()->GetWorld(), SelectedMapID);
}

void USelectWindow::OnClick_BackButton()
{
	ARPG_MenuController* PlayerController = Cast<ARPG_MenuController>(MainWidget->GetOwningPlayer());
	ARPG_MenuGameState* RPG_MenuGameState = Cast<ARPG_MenuGameState>(PlayerController->GetWorld()->GetGameState());
	if (RPG_MenuGameState)
	{
		RPG_MenuGameState->MenuState = EGameMenuState::MainMenu;

		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(PlayerController->GetHUD());
		RPG_HUD->OpenWindowNew<UMainMenuWindow>();
		if (IsValid(PlayerController->PreviewCharacter))
		{
			PlayerController->PreviewCharacter->SetActorHiddenInGame(true);
		}
	}
}

void USelectWindow::OnSelectedCharacter(int32 ItemIndex, UWidget* SelectedWidget)
{
	UCharacterSelectElem* CharacterSelectElem = Cast<UCharacterSelectElem>(SelectedWidget);
	if (CharacterSelectElem)
	{
		ARPG_MenuController* PlayerController = Cast<ARPG_MenuController>(MainWidget->GetOwningPlayer());
		if (PlayerController)
		{
			SelectedCharacterID = CharacterSelectElem->CharacterID;
			PlayerController->SetPreviewCharacter(CharacterSelectElem->CharacterID);
			if (IsValid(PlayerController->PreviewCharacter))
			{
				PlayerController->PreviewCharacter->SetActorHiddenInGame(false);
			}			
		}
	}
}

void USelectWindow::OnSelectedMap(int32 ItemIndex, UWidget* SelectedWidget)
{
	UCharacterSelectElem* MapSelectElem = Cast<UCharacterSelectElem>(SelectedWidget);
	if (MapSelectElem)
	{
		SelectedMapID = MapSelectElem->CharacterID;
	}
}