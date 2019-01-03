// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RPG_BaseEnemy.generated.h"

/*
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Jump
};
*/





UCLASS()
class STUDYRPG_REV2_API ARPG_BaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARPG_BaseEnemy();
	ARPG_BaseEnemy(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetSightRange() { return 1000.0f; }



public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARPG_BaseEnemy")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARPG_BaseEnemy")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARPG_BaseEnemy")
	class URPG_EnemyMovementComponentBase* EnemyMovementComponent;	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ARPG_BaseEnemy")
	class UArrowComponent* ArrowComponent;
};
