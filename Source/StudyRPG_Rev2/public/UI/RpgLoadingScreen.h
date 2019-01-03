// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RpgWidgetElem.h"
#include "RpgLoadingScreen.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URpgLoadingScreen : public URpgWidgetElem
{
	GENERATED_BODY()
	
	
public:
	static int32 GetTableID() { return 11; }

	virtual void AssignComponents();

	void SetLoadingImage(const FString& LoadingImagePath);

public:
	UPROPERTY()
	class UImage* _LoadingImage;
};
