// Fill out your copyright notice in the Description page of Project Settings.

#include "WindowBase.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Animation/WidgetAnimation.h"
#include "Table/Rpg_TableDef.h"

bool UWindowBase::LoadWidget(APlayerController* PlayerController)
{
	if (nullptr == PlayerController)
		return false;

	WindowInfoTB = URpgGamePlayStatics::FindTable<FWindowInfoTB>(WindowTableID);
	if (nullptr == WindowInfoTB)
		return false;

	UClass* WidgetClass = URpgGamePlayStatics::LoadClassFromPath(UUserWidget::StaticClass(), WindowInfoTB->WidgetRefPath);
	if (nullptr == WidgetClass)
		return false;

	MainWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
	MainWidget->bIsFocusable = true;
	AssignWidgetAnimations();
	AssignComponents();


	return true;
}

void UWindowBase::AssignWidgetAnimations()
{
	UClass* WidgetClass = URpgGamePlayStatics::LoadClassFromPath(UUserWidget::StaticClass(), WindowInfoTB->WidgetRefPath);
	UProperty* prop = WidgetClass->PropertyLink;
	while (nullptr != prop)
	{
		if (prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* objectProp = Cast<UObjectProperty>(prop);
			if (objectProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* object = objectProp->GetObjectPropertyValue_InContainer(MainWidget);
				UWidgetAnimation* widgetAnim = Cast<UWidgetAnimation>(object);
				if (nullptr != widgetAnim)
				{
					WidgetAnimationList.Add(prop->GetFName().ToString(), widgetAnim);
				}
			}
		}

		prop = prop->PropertyLinkNext;
	}
}