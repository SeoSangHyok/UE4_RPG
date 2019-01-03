// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WindowBase.h"
//#include "UI/RpgScrollBox.h"
#include "SelectWindow.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API USelectWindow : public UWindowBase
{
	GENERATED_BODY()
	
	USelectWindow(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void AssignComponents();

public:
	virtual void OnOpened();

	UFUNCTION()
	void OnClick_StartButton();

	UFUNCTION()
	void OnClick_BackButton();

	UFUNCTION()
	void OnSelectedCharacter(int32 ItemIndex, UWidget* SelectedWidget);

	UFUNCTION()
	void OnSelectedMap(int32 ItemIndex, UWidget* SelectedWidget);

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* StartButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class URpgScrollBox* CharacterList;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class URpgScrollBox* MapList;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* ClearCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* DieCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* DamageToEnemy;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UTextBlock* DamageFromEnemy;


	int32 SelectedCharacterID = 0;
	int32 SelectedMapID = 0;
};
