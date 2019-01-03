// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/RpgCameraActor.h"
#include "RpgSecurityCamera.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARpgSecurityCamera : public ARpgCameraActor
{
	GENERATED_BODY()
	
public:
	virtual void OnCameraUpdate(float DeltaTime);
	virtual void OnReleaseMainViewTarget();	
};
