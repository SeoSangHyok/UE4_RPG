// Fill out your copyright notice in the Description page of Project Settings.

#include "Rpg_BaseController.h"
#include "../Camera/RpgCameraManager.h"
#include "Camera/RpgCameraActor.h"
#include "Engine/World.h"
#include "../Character/RPG_BaseCharacter.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "UI/RPG_HUD.h"
#include "UI/IngameWindow.h"
#include "Table/Rpg_TableDef.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"


ARpg_BaseController::ARpg_BaseController(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ARpgCameraManager::StaticClass();
}

void ARpg_BaseController::BeginPlay()
{
	Super::BeginPlay();

	ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(GetHUD());
	UIngameWindow* IngameWindow = RPG_HUD->OpenWindowNew<UIngameWindow>();
	ARPG_BaseCharacter* RPG_BaseCharacter = Cast<ARPG_BaseCharacter>(GetPawn());
	if (IsValid(RPG_BaseCharacter) && nullptr != RPG_BaseCharacter->CharacterInfoTB)
	{
		IngameWindow->SetCharacterName(RPG_BaseCharacter->CharacterInfoTB->CharacterName);
		IngameWindow->SetCharacterThumbnail(RPG_BaseCharacter->CharacterInfoTB->Thumbnail);
		IngameWindow->SetCharacterHP(RPG_BaseCharacter->CurrentHP / RPG_BaseCharacter->CharacterInfoTB->HP);
	}

//	URpgGamePlayStatics::FindTable<FCharacterInfoTB>(RPG_BaseCharacter->CharacterInfoTableID);

	bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
}

void ARpg_BaseController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	ARPG_BaseCharacter* RpgBaseCharacter = Cast<ARPG_BaseCharacter>(aPawn);
	if (IsValid(RpgBaseCharacter))
	{
		CreateCameraAndCameraViewTarget(RpgBaseCharacter->GetCharacterDefaultCameraClass(), RpgBaseCharacter);
	}
}

void ARpg_BaseController::CreateCameraAndCameraViewTarget(TSubclassOf<ACameraActor>CameraClass, class AActor* CameraViewTarget, float BlendTime, enum EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing)
{
	ACameraActor* CameraActor = GetWorld()->SpawnActor<ACameraActor>(CameraClass);
	SetCameraAndCameraViewTarget(CameraActor, CameraViewTarget, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
}

void ARpg_BaseController::SetCameraAndCameraViewTarget(ACameraActor* CameraActor, class AActor* CameraViewTarget, float BlendTime, enum EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing)
{
	ARpgCameraActor* RpgCameraActor = Cast<ARpgCameraActor>(CameraActor);
	if (IsValid(RpgCameraActor))
	{
		RpgCameraActor->SetTargetActor(CameraViewTarget);
	}

	SetViewTargetWithBlend(CameraActor, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
}

ACameraActor* ARpg_BaseController::GetViewTargetCamera()
{
	return Cast<ACameraActor>(PlayerCameraManager->GetViewTarget());
}

void ARpg_BaseController::SetupInputComponent()
{
	Super::SetupInputComponent();
}