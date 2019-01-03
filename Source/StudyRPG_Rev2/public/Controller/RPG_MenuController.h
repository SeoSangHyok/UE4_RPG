// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPG_MenuController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARPG_MenuController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetPreviewCharacter(int32 CharacterTableId);

public:
	UPROPERTY()
	AActor* PreviewCharacter;
};
