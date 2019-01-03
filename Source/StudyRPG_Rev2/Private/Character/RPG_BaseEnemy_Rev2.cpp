// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_BaseEnemy_Rev2.h"
#include "GamePlayStatics/RpgGamePlayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimInstance.h"
#include "Animation/RpgMonsterAnimInstance.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "Controller/Rpg_MonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "GameMode/RPG_PlayGameState.h"

// Sets default values
ARPG_BaseEnemy_Rev2::ARPG_BaseEnemy_Rev2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp"));
	WeaponComp->SetupAttachment(GetRootComponent());

	ArmorComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmorComp"));
	ArmorComp->SetupAttachment(GetRootComponent());
}

void ARPG_BaseEnemy_Rev2::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadMonsterByTable(MonsterInfoTableID);
}

void ARPG_BaseEnemy_Rev2::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	LoadMonsterByTable(MonsterInfoTableID);
}

bool ARPG_BaseEnemy_Rev2::LoadMonsterByTable(int32 TableID)
{
	const FMonsterInfoTB* FindedMonsterInfoTB = URpgGamePlayStatics::FindTable<FMonsterInfoTB>(TableID);
	if (nullptr == FindedMonsterInfoTB)
		return false;

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (!IsValid(SkeletalMeshComponent))
		return false;

	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(URpgGamePlayStatics::LoadObjectFromPath(UObject::StaticClass(), FindedMonsterInfoTB->SkeletalMesh));
	if (!IsValid(SkeletalMesh))
		return false;

	MonsterInfoTB = FindedMonsterInfoTB;

	MonsterInfoTableID = TableID;

	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	SkeletalMeshComponent->SetRelativeRotation(FRotator(0.0f, MonsterInfoTB->DefaultRotateYaw, 0.0f));
	SkeletalMeshComponent->SetRelativeLocation(FVector(0.0f,0.0f, -MonsterInfoTB->CapsuleHalfHeight));

	UClass* AnimBPClass = URpgGamePlayStatics::LoadClassFromPath(UAnimInstance::StaticClass(), MonsterInfoTB->AnimationBP);
	SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SkeletalMeshComponent->SetAnimInstanceClass(AnimBPClass);

	UCapsuleComponent* EnemyCapsuleComponent = GetCapsuleComponent();
	EnemyCapsuleComponent->SetCapsuleHalfHeight(MonsterInfoTB->CapsuleHalfHeight);
	EnemyCapsuleComponent->SetCapsuleRadius(MonsterInfoTB->CapsuleRadius);

	const FEquipInfoTB* EquipInfoTB = URpgGamePlayStatics::FindTable<FEquipInfoTB>(FindedMonsterInfoTB->Weapon);
	if (nullptr != EquipInfoTB)
	{
		UStaticMesh* WeaponMesh = Cast<UStaticMesh>(URpgGamePlayStatics::LoadObjectFromPath(UObject::StaticClass(), EquipInfoTB->Mesh));
		if (nullptr != WeaponMesh)
		{
			WeaponComp->SetStaticMesh(WeaponMesh);
			WeaponComp->SetRelativeLocation(FVector(EquipInfoTB->Loc_X, EquipInfoTB->Loc_Y, EquipInfoTB->Loc_Z));
			WeaponComp->SetRelativeRotation(FRotator(EquipInfoTB->Rot_Y, EquipInfoTB->Rot_Z, EquipInfoTB->Rot_X));

			FName AttatchSocketName = FName(*EquipInfoTB->AttatchedSocket);
			WeaponComp->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::KeepRelativeTransform, AttatchSocketName);
		}
	}
	else
	{
		WeaponComp->SetStaticMesh(nullptr);
	}

	EquipInfoTB = URpgGamePlayStatics::FindTable<FEquipInfoTB>(FindedMonsterInfoTB->Armor);
	if (nullptr != EquipInfoTB)
	{
		UStaticMesh* ArmorMesh = Cast<UStaticMesh>(URpgGamePlayStatics::LoadObjectFromPath(UObject::StaticClass(), EquipInfoTB->Mesh));
		if (nullptr != ArmorMesh)
		{
			ArmorComp->SetStaticMesh(ArmorMesh);
			ArmorComp->SetRelativeLocation(FVector(EquipInfoTB->Loc_X, EquipInfoTB->Loc_Y, EquipInfoTB->Loc_Z));
			ArmorComp->SetRelativeRotation(FRotator(EquipInfoTB->Rot_Y, EquipInfoTB->Rot_Z, EquipInfoTB->Rot_X));

			FName AttatchSocketName = FName(*EquipInfoTB->AttatchedSocket);
			ArmorComp->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttatchSocketName);
		}
	}
	else
	{
		ArmorComp->SetStaticMesh(nullptr);
	}

	GetCharacterMovement()->MaxWalkSpeed = MonsterInfoTB->Speed;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = Instigator;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = GetLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save AI controllers into a map
	AAIController* AiController = GetWorld()->SpawnActor<AAIController>(ARpg_MonsterController::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnInfo);
	AiController->Possess(this);

	UBehaviorTree* BehaviorTree = Cast<UBehaviorTree>(URpgGamePlayStatics::LoadObjectFromPath(UBehaviorTree::StaticClass(), MonsterInfoTB->BehaviourTree));
	AiController->RunBehaviorTree(BehaviorTree);

	CurrentHP = FindedMonsterInfoTB->HP;


	return true;
}

// Called when the game starts or when spawned
void ARPG_BaseEnemy_Rev2::BeginPlay()
{
	Super::BeginPlay();

	HomePosition = GetActorLocation();
}

// Called every frame
void ARPG_BaseEnemy_Rev2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPG_BaseEnemy_Rev2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ARPG_BaseEnemy_Rev2::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHP == 0.0f)
		return 0.0f;

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP = FMath::Max<float>(0.0f, CurrentHP - DamageAmount);

	ARPG_PlayGameState* RPG_PlayGameState = Cast<ARPG_PlayGameState>(URpgGamePlayStatics::GetGameState(GetWorld()));
	RPG_PlayGameState->DamageToEnemy += (int)DamageAmount;

	if (CurrentHP == 0.0f)
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		URpgMonsterAnimInstance* RpgMonsterAnimInstance = Cast<URpgMonsterAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
		RpgMonsterAnimInstance->DeathMotionIdx = FMath::Rand() % 2;

		AAIController* AiController = Cast<AAIController>(GetController());
		UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(AiController->GetBrainComponent());
		BTComp->StopTree();

		GetCapsuleComponent()->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));

		if (RPG_PlayGameState)
		{
			RPG_PlayGameState->MonsterDead(MonsterInfoTableID);
		}
	}

	return DamageAmount;
}

#if WITH_EDITOR
void ARPG_BaseEnemy_Rev2::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
/*
	FName ChangedPropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.GetPropertyName() : "";

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(ARPG_BaseEnemy_Rev2, MonsterInfoTableID))
	{
		LoadMonsterByTable(MonsterInfoTableID);
	}
*/
}
#endif