// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/RpgCameraActor.h"
#include "RpgCharacterCamera.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARpgCharacterCamera : public ARpgCameraActor
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void OnCameraUpdate(float DeltaTime);
	virtual void OnReleaseMainViewTarget();
	virtual FVector GetCameraDirection();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARpgCameraActor", meta = (AllowPrivateAccess = "true"))
	FRotator CameraRotOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARpgCameraActor", meta = (AllowPrivateAccess = "true"))
	float TargetDistance;
};
