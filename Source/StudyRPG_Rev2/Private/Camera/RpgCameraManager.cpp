// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgCameraManager.h"
#include "Engine/World.h"
#include "../GamePlayStatics/RpgGamePlayStatics.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Camera/RpgCameraActor.h"



/** After updating camera, inform pawn to update 1p mesh to match camera's location&rotation */
void ARpgCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	ARpgCameraActor* RpgCameraActor = Cast<ARpgCameraActor>(GetViewTarget());
	if (IsValid(RpgCameraActor))
	{
		RpgCameraActor->OnCameraUpdate(DeltaTime);
	}
}

void ARpgCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void ARpgCameraManager::SetViewTarget(class AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams)
{
	if (!IsValid(NewViewTarget))
		return;

	ARpgCameraActor* PrevRpgCameraActor = Cast<ARpgCameraActor>(ViewTarget.Target);
	if (IsValid(PrevRpgCameraActor))
	{
		PrevRpgCameraActor->OnReleaseMainViewTarget();
	}

	Super::SetViewTarget(NewViewTarget, TransitionParams);
}