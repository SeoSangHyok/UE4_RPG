// Fill out your copyright notice in the Description page of Project Settings.

#include "TestListView.h"



#define LOCTEXT_NAMESPACE "UMG"

#if WITH_EDITOR
const FText UTestListView::GetPaletteCategory()
{
	return LOCTEXT("Misc_Rpg", "Misc_Rpg");
}
#endif

#undef LOCTEXT_NAMESPACE