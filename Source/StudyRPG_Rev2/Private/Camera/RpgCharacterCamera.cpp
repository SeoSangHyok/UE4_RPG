// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgCharacterCamera.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "RpgGamePlayStatics.h"

ARpgCharacterCamera::ARpgCharacterCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CameraRotOffset.Yaw = 0.0f;
	CameraRotOffset.Pitch = -40.0f;
	CameraRotOffset.Roll = 0.0f;

	TargetDistance = 400.0f;
}

void ARpgCharacterCamera::OnCameraUpdate(float DeltaTime)
{
	if (!IsValid(MainViewTargetActor))
		return;

	FRotator RotResult = CameraRotOffset;
	APlayerController* PC = URpgGamePlayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(PC))
	{
		FRotator ControlRotation = PC->GetControlRotation();

		RotResult.Add(-ControlRotation.Pitch, ControlRotation.Yaw, 0.0f);
	}

	SetActorRotation(RotResult);
	FVector CameraPos = MainViewTargetActor->GetActorLocation() - (RotResult.Vector() * TargetDistance);

	SetActorLocation(CameraPos);
}

void ARpgCharacterCamera::OnReleaseMainViewTarget()
{
	MainViewTargetActor = nullptr;
	Destroy();
}

FVector ARpgCharacterCamera::GetCameraDirection()
{
	FVector RetVal = GetActorRotation().Vector();

	if (IsValid(MainViewTargetActor))
	{
		RetVal = MainViewTargetActor->GetActorLocation() - GetActorLocation();
		RetVal.Normalize();
	}

	return RetVal;
}