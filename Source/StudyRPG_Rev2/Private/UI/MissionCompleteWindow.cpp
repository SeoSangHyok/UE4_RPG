// Fill out your copyright notice in the Description page of Project Settings.

#include "MissionCompleteWindow.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "GameMode/RPGGameInstance.h"
#include "Controller/Rpg_BaseController.h"




UMissionCompleteWindow::UMissionCompleteWindow(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	WindowTableID = 3;
}

void UMissionCompleteWindow::AssignComponents()
{
	_CompleteText = Cast<UTextBlock>(MainWidget->GetWidgetFromName(TEXT("CompleteText")));
	_OkButton = Cast<UButton>(MainWidget->GetWidgetFromName(TEXT("OkButton")));
	_OkButton->OnClicked.AddDynamic(this, &UMissionCompleteWindow::OnClick_OkButton);
}

void UMissionCompleteWindow::SetCompleteText(const FString& CompleteText)
{
	_CompleteText->SetText(FText::FromString(CompleteText));
}

void UMissionCompleteWindow::OnClick_OkButton()
{
	ARpg_BaseController* PlayerController = Cast<ARpg_BaseController>(MainWidget->GetOwningPlayer());
	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(PlayerController->GetWorld()->GetGameInstance());
	if (RPGGameInstance)
	{
		RPGGameInstance->FromGamePlay = true;
	}

	UGameplayStatics::OpenLevel(MainWidget->GetOwningPlayer()->GetWorld(), TEXT("/Game/Map/Start"));
}

