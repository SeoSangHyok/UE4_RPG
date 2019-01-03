// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "RpgScrollBox.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRpgScrollBoxSelectItem, int32, ItemIndex, UWidget*, SelectedWidget);

UCLASS()
class STUDYRPG_REV2_API URpgScrollBox : public UScrollBox
{
	GENERATED_BODY()
	
public:
	// UPanelWidget
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	// End UPanelWidget

	void SetItemSelectByListIndex(int32 ListIndex, bool bScrollToItem = false);
	void SetItemSelectByWidgetItem(class URpgScrollBoxElem* RpgScrollBoxElem, bool bScrollToItem = false);

#if WITH_EDITOR
	//~ Begin UWidget Interface
	virtual const FText GetPaletteCategory() override;
	//~ End UWidget Interface
#endif	

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<class URpgScrollBoxElem*> ListItems;

	UPROPERTY(BlueprintReadOnly)
	int32 SelectedItemIndex;

	UPROPERTY()
	FOnRpgScrollBoxSelectItem OnRpgScrollBoxSelectItem;
};
