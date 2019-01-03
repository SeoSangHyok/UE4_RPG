// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WindowBase.h"
#include "Blueprint/UserWidget.h"
#include "IngameWindow.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UIngameWindow : public UWindowBase
{
	GENERATED_BODY()
	
	UIngameWindow(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void AssignComponents();

public:
	virtual void OnOpened();
	void SetCharacterName(const FString& CharacterName);
	void SetCharacterThumbnail(const FString& ThumbnailPath);
	void SetCharacterHP(float HpRate);

public:
	UPROPERTY()
	class UImage* _Thumbnail;

	UPROPERTY()
	class UTextBlock* _CharacterName;

	UPROPERTY()
	class UProgressBar* _CharacterHP;
};
