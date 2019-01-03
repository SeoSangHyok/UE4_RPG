// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/RpgWidgetElem.h"
#include "RpgScrollBoxElem.h"
#include "CharacterSelectElem.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UCharacterSelectElem : public URpgScrollBoxElem
{
	GENERATED_BODY()

public:
	static int32 GetTableID() { return 10; }
	
	virtual void AssignComponents();
	
	virtual void SetSelected(bool Selected);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	UPROPERTY()
	class UImage* _Thumbnail;

	UPROPERTY()
	class UTextBlock* _CharacterName;

	UPROPERTY()
	class UBorder* _ItemBorder;

	UPROPERTY()
	int32 CharacterID;
};
