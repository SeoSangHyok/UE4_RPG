// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgCameraActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "RpgGamePlayStatics.h"

ARpgCameraActor::ARpgCameraActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MainViewTargetActor = nullptr;
}

void ARpgCameraActor::SetTargetActor(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
		return;

	MainViewTargetActor = TargetActor;
}

FVector ARpgCameraActor::GetCameraDirection()
{
	FVector RetVal = GetActorRotation().Vector();

	return RetVal;
}