// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/RpgCameraActor.h"
#include "RpgCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARpgCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	/** After updating camera, inform pawn to update 1p mesh to match camera's location&rotation */
	virtual void UpdateCamera(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void SetViewTarget(class AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams = FViewTargetTransitionParams());
};
