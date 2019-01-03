// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgLoadingScreen.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Engine/Texture2D.h"



void URpgLoadingScreen::AssignComponents()
{
	_LoadingImage = Cast<UImage>(GetWidgetFromName(TEXT("LoadingImage")));
}

void URpgLoadingScreen::SetLoadingImage(const FString& LoadingImagePath)
{
	if (_LoadingImage)
	{
		UTexture2D* LoadingImage = Cast<UTexture2D>(URpgGamePlayStatics::LoadObjectFromPath(UTexture2D::StaticClass(), LoadingImagePath));
		_LoadingImage->SetBrushFromTexture(LoadingImage);
	}
}