// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectElem.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Border.h"
#include "RpgScrollBox.h"
#include "Styling/SlateBrush.h"




void UCharacterSelectElem::AssignComponents()
{
	_Thumbnail = Cast<UImage>(GetWidgetFromName(TEXT("Thumbnail")));
	_CharacterName = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterName")));
	_ItemBorder = Cast<UBorder>(GetWidgetFromName(TEXT("ItemBorder")));
}

void UCharacterSelectElem::SetSelected(bool Selected)
{
	if (bSelected == Selected)
		return;

	Super::SetSelected(Selected);

	FLinearColor NewBorderColor = FLinearColor::Gray;
	if (Selected)
		NewBorderColor.A = 1.0;
	else
		NewBorderColor.A = 0.0f;

	_ItemBorder->SetBrushColor(NewBorderColor);

	
}

FReply UCharacterSelectElem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (MainScrollBox)
	{
		MainScrollBox->SetItemSelectByWidgetItem(this);
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}