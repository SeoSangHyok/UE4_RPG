// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RpgWidgetElem.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URpgWidgetElem : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void AssignComponents() { ; }

public:
	void AssignWidgetAnimations(UClass* WidgetBPClass);

public:
	UPROPERTY()
	TMap<FString, class UWidgetAnimation*> WidgetAnimationList;	
};