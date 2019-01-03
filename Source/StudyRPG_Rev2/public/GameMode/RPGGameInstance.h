// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init();
	
	UFUNCTION()
	void BegineLoadingScreen(const FString& MapName);

	UFUNCTION()
	void EndLoadingScreen(UWorld* InLoadedWorld);

	UFUNCTION()
	class URpgLoadingScreen* GetLoadingWidget();

public:
	UPROPERTY()
	class URpgLoadingScreen* LoadingWidget;

	bool FromGamePlay = false;

	int32 SelectedCharacterID = 0;
	int32 TargetMonsterID = 0;
};
