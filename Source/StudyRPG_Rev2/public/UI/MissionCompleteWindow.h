// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WindowBase.h"
#include "MissionCompleteWindow.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UMissionCompleteWindow : public UWindowBase
{
	GENERATED_BODY()

	UMissionCompleteWindow(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void AssignComponents();

public:
	void SetCompleteText(const FString& CompleteText);

	UFUNCTION()
	void OnClick_OkButton();
	
public:
	UPROPERTY()
	class UTextBlock* _CompleteText;

	UPROPERTY()
	class UButton* _OkButton;
};
