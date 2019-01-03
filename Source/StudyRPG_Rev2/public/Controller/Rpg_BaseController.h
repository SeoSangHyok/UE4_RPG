// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ObjectMacros.h"
#include "Rpg_BaseController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARpg_BaseController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Possess(APawn* aPawn) override;

	UFUNCTION(BlueprintCallable, Category = "ARpg_BaseController")
	void CreateCameraAndCameraViewTarget(TSubclassOf<ACameraActor>CameraClass, class AActor* CameraViewTarget, float BlendTime = 0, enum EViewTargetBlendFunction BlendFunc = VTBlend_Linear, float BlendExp = 0, bool bLockOutgoing = false);

	UFUNCTION(BlueprintCallable, Category = "ARpg_BaseController")
	void SetCameraAndCameraViewTarget(ACameraActor* CameraActor, class AActor* CameraViewTarget, float BlendTime = 0, enum EViewTargetBlendFunction BlendFunc = VTBlend_Linear, float BlendExp = 0, bool bLockOutgoing = false);

	ACameraActor* GetViewTargetCamera();

protected:
	virtual void SetupInputComponent() override;
};
