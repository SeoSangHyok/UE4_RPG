// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Rpg_MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API ARpg_MonsterController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//~ Begin AController Interface
	virtual void Possess(APawn* InPawn) override;
};
