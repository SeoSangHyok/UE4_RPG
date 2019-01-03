// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "TestListView.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API UTestListView : public UListView
{
	GENERATED_BODY()
	
#if WITH_EDITOR
		//~ Begin UWidget Interface
		virtual const FText GetPaletteCategory() override;
	//~ End UWidget Interface
#endif	
	
	
};
