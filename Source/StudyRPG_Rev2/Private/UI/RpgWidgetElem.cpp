// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgWidgetElem.h"
#include "Animation/WidgetAnimation.h"


void URpgWidgetElem::AssignWidgetAnimations(UClass* WidgetBPClass)
{
	if (nullptr == WidgetBPClass)
		return;

	UProperty* prop = WidgetBPClass->PropertyLink;
	while (nullptr != prop)
	{
		if (prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* objectProp = Cast<UObjectProperty>(prop);
			if (objectProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* object = objectProp->GetObjectPropertyValue_InContainer(this);
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