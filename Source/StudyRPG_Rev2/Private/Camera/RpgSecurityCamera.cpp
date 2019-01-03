// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgSecurityCamera.h"




void ARpgSecurityCamera::OnCameraUpdate(float DeltaTime)
{
	if (IsValid(MainViewTargetActor))
	{
		FVector EyeDirection = MainViewTargetActor->GetActorLocation() - GetActorLocation();
		EyeDirection.Normalize();

		FRotator Rotator = EyeDirection.Rotation();
		SetActorRotation(Rotator);
	}
}

void ARpgSecurityCamera::OnReleaseMainViewTarget()
{
	MainViewTargetActor = nullptr;
}