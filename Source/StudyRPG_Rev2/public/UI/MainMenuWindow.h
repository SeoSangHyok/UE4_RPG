// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "UI/WindowBase.h"
#include "MainMenuWindow.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UMainMenuWindow : public UWindowBase
{
	GENERATED_BODY()

	UMainMenuWindow(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void AssignComponents();

public:
	virtual void OnOpened();

	UFUNCTION()
	void OnClick_NewButton();

	UFUNCTION()
	void OnClick_LoadButton();

	UFUNCTION()
	void OnClick_QuitButton();

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* NewButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* LoadButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* QuitButton;
};
