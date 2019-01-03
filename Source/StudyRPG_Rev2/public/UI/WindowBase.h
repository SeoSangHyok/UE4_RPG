// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "WindowBase.generated.h"

UENUM()
enum class ERpgWindowType : uint8
{
	MainMenu = 1,
	Select,
	MissionComplete,
	IngameWindow,
	CharacterListItem = 10,
	LoadingScreen
};

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UWindowBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual bool LoadWidget(class APlayerController* PlayerController);

protected:
	virtual void AssignComponents() { ; }

public:
	virtual void OnOpened() { ; }

private:
	void AssignWidgetAnimations();

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 WindowTableID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UUserWidget* MainWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, class UWidgetAnimation*> WidgetAnimationList;

	const struct FWindowInfoTB* WindowInfoTB;
};
