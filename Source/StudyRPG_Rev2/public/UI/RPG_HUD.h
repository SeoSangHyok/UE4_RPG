// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WindowBase.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Table/Rpg_TableDef.h"
#include "RPG_HUD.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARPG_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void CloseCurrentWindow();
	void CheckNeedUIMode();

	template<typename T>
	T* OpenWindowNew()
	{
		T* Window = NewObject<T>();
		if (Window->LoadWidget(URpgGamePlayStatics::GetPlayerController(GetWorld(), 0)) == false)
			return nullptr;

		CloseCurrentWindow();
		CurrentOpenedWindow = Window;
		CurrentOpenedWindow->MainWidget->AddToViewport();

		Window->OnOpened();
		CheckNeedUIMode();

		return Window;
	}
	
	template<typename T>
	static T* CreateRpgWidget(APlayerController* WidgetPlayerOwner)
	{
		const FWindowInfoTB* WindowInfoTB = URpgGamePlayStatics::FindTable<FWindowInfoTB>(T::GetTableID());
		if (nullptr == WindowInfoTB)
			return nullptr;

		UClass* WidgetClass = URpgGamePlayStatics::LoadClassFromPath(T::StaticClass(), WindowInfoTB->WidgetRefPath);
		if (nullptr == WidgetClass)
			return nullptr;

		T* NewWidget = CreateWidget<T>(WidgetPlayerOwner, WidgetClass);
		if (nullptr != NewWidget)
		{
			NewWidget->AssignWidgetAnimations(WidgetClass);
			NewWidget->AssignComponents();
		}

		return NewWidget;
	}

	template<typename T>
	static T* CreateRpgWidgetByGameInstance(UGameInstance* GameInstance)
	{
		const FWindowInfoTB* WindowInfoTB = URpgGamePlayStatics::FindTable<FWindowInfoTB>(T::GetTableID());
		if (nullptr == WindowInfoTB)
			return nullptr;

		UClass* WidgetClass = URpgGamePlayStatics::LoadClassFromPath(T::StaticClass(), WindowInfoTB->WidgetRefPath);
		if (nullptr == WidgetClass)
			return nullptr;

		T* NewWidget = CreateWidget<T>(GameInstance, WidgetClass);
		if (nullptr != NewWidget)
		{
			NewWidget->AssignWidgetAnimations(WidgetClass);
			NewWidget->AssignComponents();
		}

		return NewWidget;
	}

public:
	UPROPERTY()
	UWindowBase* CurrentOpenedWindow;
};
