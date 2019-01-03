// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpgWidgetElem.h"
#include "RpgScrollBoxElem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STUDYRPG_REV2_API URpgScrollBoxElem : public URpgWidgetElem
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void RegisterToScrollBox(class URpgScrollBox* RpgScrollBox) { MainScrollBox = RpgScrollBox; }

	UFUNCTION()
	virtual void SetSelected(bool Selected) { bSelected = Selected; }

	UFUNCTION()
	virtual bool IsSelected() { return bSelected; }

public:
	UPROPERTY()
	class URpgScrollBox* MainScrollBox = nullptr;

	UPROPERTY()
	bool bSelected = false;
};
