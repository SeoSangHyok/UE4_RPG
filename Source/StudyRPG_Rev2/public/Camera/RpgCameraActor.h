// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "RpgCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARpgCameraActor : public ACameraActor
{
	GENERATED_UCLASS_BODY()

public:
	virtual void OnCameraUpdate(float DeltaTime) { ; }
	virtual void SetTargetActor(AActor* TargetActor);
	virtual void OnReleaseMainViewTarget() { ; }

	virtual FVector GetCameraDirection();

protected:
	UPROPERTY(BlueprintReadOnly, VIsibleAnywhere, Category = "ARpgCameraActor", meta = (AllowPrivateAccess = "true"))
	AActor* MainViewTargetActor;
};
