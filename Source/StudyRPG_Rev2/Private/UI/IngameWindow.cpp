// Fill out your copyright notice in the Description page of Project Settings.

#include "IngameWindow.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Engine/Texture2D.h"




UIngameWindow::UIngameWindow(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	WindowTableID = 4;
}

void UIngameWindow::OnOpened()
{

}

void UIngameWindow::AssignComponents()
{
	UWidget* FindWidget = MainWidget->GetWidgetFromName(TEXT("Thumbnail"));
	_Thumbnail = Cast<UImage>(FindWidget);


	FindWidget = MainWidget->GetWidgetFromName(TEXT("CharacterName"));
	_CharacterName = Cast<UTextBlock>(FindWidget);

	FindWidget = MainWidget->GetWidgetFromName(TEXT("CharacterHP"));
	_CharacterHP = Cast<UProgressBar>(FindWidget);
}

void UIngameWindow::SetCharacterName(const FString& CharacterName)
{
	_CharacterName->SetText(FText::FromString(CharacterName));
}

void UIngameWindow::SetCharacterThumbnail(const FString& ThumbnailPath)
{
	UTexture2D* ThumbNailImage = Cast<UTexture2D>(URpgGamePlayStatics::LoadObjectFromPath(UTexture2D::StaticClass(), ThumbnailPath));

	_Thumbnail->SetBrushFromTexture(ThumbNailImage);
}

void UIngameWindow::SetCharacterHP(float HpRate)
{
	_CharacterHP->SetPercent(HpRate);
}