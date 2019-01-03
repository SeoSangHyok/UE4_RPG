// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameInstance.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "UI/RpgLoadingScreen.h"
#include "UI/RPG_HUD.h"
#include "RpgSaveGame.h"



void URPGGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &URPGGameInstance::BegineLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &URPGGameInstance::EndLoadingScreen);
}

void URPGGameInstance::BegineLoadingScreen(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	if (LoadingWidget)
	{
		LoadingScreenAttributes.WidgetLoadingScreen = GetLoadingWidget()->TakeWidget();
	}
	else
	{
		LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
	}

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
	GetMoviePlayer()->PlayMovie();
}

URpgLoadingScreen* URPGGameInstance::GetLoadingWidget()
{
	if (LoadingWidget != nullptr)
	{
		return LoadingWidget;
	}
	else
	{
		LoadingWidget = ARPG_HUD::CreateRpgWidgetByGameInstance<URpgLoadingScreen>(this);
		return LoadingWidget;
	}
}

void URPGGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	LoadingWidget = nullptr;
}