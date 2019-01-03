// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_HUD.h"
#include "UI/MainMenuWindow.h"
#include "Controller/RPG_MenuController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"





void ARPG_HUD::BeginPlay()
{
	Super::BeginPlay();

	//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetOwningPlayerController());
	//CurrentOpenedWindow = nullptr;
}

void ARPG_HUD::CloseCurrentWindow()
{
	if (CurrentOpenedWindow)
	{
		CurrentOpenedWindow->MainWidget->RemoveFromViewport();
		CurrentOpenedWindow = nullptr;
		CheckNeedUIMode();
	}
}

void ARPG_HUD::CheckNeedUIMode()
{
	bool NeedUIMode = false;

	if (nullptr != CurrentOpenedWindow && CurrentOpenedWindow->WindowInfoTB->NeedUIMode == true)
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayerController(), CurrentOpenedWindow->MainWidget, EMouseLockMode::DoNotLock);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayerController());
	}
}