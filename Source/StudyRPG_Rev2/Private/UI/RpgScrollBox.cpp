// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgScrollBox.h"
#include "RpgScrollBoxElem.h"
#include "Kismet/KismetSystemLibrary.h"

#define LOCTEXT_NAMESPACE "UMG"

void URpgScrollBox::OnSlotAdded(UPanelSlot* Slot)
{
	Super::OnSlotAdded(Slot);

	URpgScrollBoxElem* RpgScrollBoxElem = Cast<URpgScrollBoxElem>(Slot->Content);
	if (RpgScrollBoxElem)
	{
		RpgScrollBoxElem->RegisterToScrollBox(this);
		ListItems.Add(RpgScrollBoxElem);
	}
}

void URpgScrollBox::OnSlotRemoved(UPanelSlot* Slot)
{
	Super::OnSlotRemoved(Slot);

	URpgScrollBoxElem* RpgScrollBoxElem = Cast<URpgScrollBoxElem>(Slot->Content);
	if (RpgScrollBoxElem)
	{
		RpgScrollBoxElem->RegisterToScrollBox(nullptr);

		int i = 0;
		for (auto It = ListItems.CreateIterator() ; It ; ++It)
		{
			if (*It == RpgScrollBoxElem)
			{
				ListItems.RemoveAt(i);
				break;
			}
			i++;
		}
	}
}

void URpgScrollBox::SetItemSelectByListIndex(int32 ListIndex, bool bScrollToItem/* = false*/)
{
	if (SelectedItemIndex >= ListItems.Num())
		return;

	URpgScrollBoxElem* PrevSelectedItem = ListItems[SelectedItemIndex];
	PrevSelectedItem->SetSelected(false);

	SelectedItemIndex = ListIndex;
	URpgScrollBoxElem* SelectedItem = ListItems[SelectedItemIndex];
	SelectedItem->SetSelected(true);

	if (bScrollToItem)
	{
		ScrollWidgetIntoView(SelectedItem, true, EDescendantScrollDestination::Center);
	}
}

void URpgScrollBox::SetItemSelectByWidgetItem(URpgScrollBoxElem* RpgScrollBoxElem, bool bScrollToItem/* = false*/)
{
	for (int i=0 ; i<ListItems.Num() ; i++)
	{
		if (RpgScrollBoxElem == ListItems[i])
		{
			URpgScrollBoxElem* PrevSelectedItem = ListItems[SelectedItemIndex];
			PrevSelectedItem->SetSelected(false);

			SelectedItemIndex = i;
			ListItems[i]->SetSelected(true);

			if (bScrollToItem)
			{
				ScrollWidgetIntoView(ListItems[i], true, EDescendantScrollDestination::Center);
			}

			if (OnRpgScrollBoxSelectItem.IsBound())
			{
				OnRpgScrollBoxSelectItem.Broadcast(i, ListItems[i]);
			}
			break;
		}
	}
}

#if WITH_EDITOR
const FText URpgScrollBox::GetPaletteCategory()
{
	return LOCTEXT("Panel_Rpg", "Panel_Rpg");
}
#endif

#undef LOCTEXT_NAMESPACE