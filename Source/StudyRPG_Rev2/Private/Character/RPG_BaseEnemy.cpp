// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/RPG_EnemyMovementComponentBase.h"
#include "Components/ArrowComponent.h"


// Sets default values
ARPG_BaseEnemy::ARPG_BaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ARPG_BaseEnemy::ARPG_BaseEnemy(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
//	class UCapsuleComponent* CapsuleComponent;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

//	class UArrowComponent* ArrowComponent;
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(GetRootComponent());

//	class USkeletalMeshcomponent* SkeletalMeshComponent;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());


//	class URPG_EnemyMovementComponentBase* EnemyMovementComponent;
	EnemyMovementComponent = CreateDefaultSubobject<URPG_EnemyMovementComponentBase>(TEXT("EnemyMovementComponent"));
	EnemyMovementComponent->UpdatedComponent = CapsuleComponent;
}

// Called when the game starts or when spawned
void ARPG_BaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPG_BaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPG_BaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

