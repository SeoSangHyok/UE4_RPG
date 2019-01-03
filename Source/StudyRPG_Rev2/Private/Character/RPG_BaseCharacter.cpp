// Fill out your copyright notice in the Description page of Project Settings.
#include "RPG_BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"	//<-- Use For SpringArmComponent
#include "Camera/CameraComponent.h"				//<-- Use For CameraComponent

#include "RpgGamePlayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"

#include "Rpg_TableDef.h"
#include "RPG_TableLoader.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/RpgCharacterAniminstance.h"
#include "Camera/RpgCameraActor.h"
#include "Camera/RpgCharacterCamera.h"
#include "../Controller/Rpg_BaseController.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UI/RPG_HUD.h"
#include "UI/IngameWindow.h"
#include "UI/MissionCompleteWindow.h"
#include "GameMode/RPGGameInstance.h"
#include "GameMode/RPG_PlayGameState.h"

// Sets default values
ARPG_BaseCharacter::ARPG_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	FRotator Rotator;
	Rotator.Pitch = -15.0f;
	SpringArm->SetRelativeRotation(Rotator);
	SpringArm->TargetArmLength = 450.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	WeaponComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComp"));

	CharacterState = ECharacterState::Idle;
}

// Called when the game starts or when spawned
void ARPG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	ARpg_BaseController* Rpg_BaseController = Cast<ARpg_BaseController>(GetController());
	if (Rpg_BaseController)
	{
		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(Rpg_BaseController->GetHUD());
		if (RPG_HUD)
		{
			UIngameWindow* IngameWindow = Cast<UIngameWindow>(RPG_HUD->CurrentOpenedWindow);
			if (IngameWindow)
			{
				IngameWindow->SetCharacterName(CharacterInfoTB->CharacterName);
				IngameWindow->SetCharacterThumbnail(CharacterInfoTB->Thumbnail);
				IngameWindow->SetCharacterHP(1.0f);
			}
		}
	}

	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(GetController()->GetWorld()->GetGameInstance());
	if (RPGGameInstance && RPGGameInstance->SelectedCharacterID != 0)
	{
		LoadSkeletalMeshByTable(RPGGameInstance->SelectedCharacterID);
	}
}

// Called every frame
void ARPG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetMovementComponent()->IsFalling())
	{
		CharacterState = ECharacterState::Idle;
	}

}

// Called to bind functionality to input
void ARPG_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ARPG_BaseCharacter::Jump);
	PlayerInputComponent->BindAction("Skill_Melee", EInputEvent::IE_Pressed, this, &ARPG_BaseCharacter::Skill_Melee);
	PlayerInputComponent->BindAction("Skill_Range", EInputEvent::IE_Pressed, this, &ARPG_BaseCharacter::Skill_Range);

	PlayerInputComponent->BindAxis("MoveFoward", this, &ARPG_BaseCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPG_BaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraTurnYaw", this, &ARPG_BaseCharacter::CameraTurnYaw);
	PlayerInputComponent->BindAxis("CameraTurnPitch", this, &ARPG_BaseCharacter::CameraTurnPitch);
}

void ARPG_BaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadSkeletalMeshByTable(CharacterInfoTableID);

	UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement();
	CharacterMovementComp->bUseControllerDesiredRotation = false;
	CharacterMovementComp->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	SpringArm->bEnableCameraRotationLag = true;
}

void ARPG_BaseCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	LoadSkeletalMeshByTable(CharacterInfoTableID);
}

bool ARPG_BaseCharacter::LoadSkeletalMeshByTable(int32 TableID)
{
	CharacterInfoTB = URpgGamePlayStatics::FindTable<FCharacterInfoTB>(TableID);

	if (nullptr == CharacterInfoTB)
		return false;

	USkeletalMeshComponent* SkeletalMeshCopm = GetMesh();

	if (!IsValid(SkeletalMeshCopm))
		return false;

	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(URpgGamePlayStatics::LoadObjectFromPath(UObject::StaticClass(), CharacterInfoTB->SkeletalMesh));
	if (!IsValid(SkeletalMesh))
		return false;

	SkeletalMeshCopm->SetSkeletalMesh(SkeletalMesh);
	SkeletalMeshCopm->SetRelativeRotation(FRotator(0.0f, CharacterInfoTB->DefaultRotateYaw, 0.0f));
	SkeletalMeshCopm->SetRelativeLocation(FVector(0.0f,0.0f,-CharacterInfoTB->CapsuleHalfHeight));
	SkeletalMeshCopm->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	UClass* AnimInstaceClass = URpgGamePlayStatics::LoadClassFromPath(UAnimInstance::StaticClass(), CharacterInfoTB->AnimationBP);

	SkeletalMeshCopm->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SkeletalMeshCopm->SetAnimInstanceClass(AnimInstaceClass);

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCapsuleHalfHeight(CharacterInfoTB->CapsuleHalfHeight);
	CapsuleComp->SetCapsuleRadius(CharacterInfoTB->CapsuleRadius);

	if (0 != CharacterInfoTB->Weapon)
	{
		const FEquipInfoTB* EquipInfoTB = URpgGamePlayStatics::FindTable<FEquipInfoTB>(CharacterInfoTB->Weapon);
		if (nullptr != EquipInfoTB)
		{
			USkeletalMesh* WeaponSkeletalMesh = Cast<USkeletalMesh>(URpgGamePlayStatics::LoadObjectFromPath(UObject::StaticClass(), EquipInfoTB->Mesh));
			WeaponComp->SetSkeletalMesh(WeaponSkeletalMesh);

			FName AttatchSocketName = FName(*EquipInfoTB->AttatchedSocket);
			WeaponComp->AttachToComponent(SkeletalMeshCopm, FAttachmentTransformRules::SnapToTargetIncludingScale, AttatchSocketName);
		}
		else
		{
			WeaponComp->SetSkeletalMesh(nullptr);
		}
	}
	else
	{
		WeaponComp->SetSkeletalMesh(nullptr);
	}

	CurrentHP = CharacterInfoTB->HP;
	
	ARpg_BaseController* Rpg_BaseController = Cast<ARpg_BaseController>(GetController());
	if (Rpg_BaseController)
	{
		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(Rpg_BaseController->GetHUD());
		if (RPG_HUD)
		{
			UIngameWindow* IngameWindow = Cast<UIngameWindow>(RPG_HUD->CurrentOpenedWindow);
			if (IngameWindow)
			{
				IngameWindow->SetCharacterName(CharacterInfoTB->CharacterName);
				IngameWindow->SetCharacterThumbnail(CharacterInfoTB->Thumbnail);
				IngameWindow->SetCharacterHP(CurrentHP / CharacterInfoTB->HP);
			}
		}
	}

	return true;
}

void ARPG_BaseCharacter::Jump()
{
	if (!CheckJumpEnable())
		return;

	CharacterState = ECharacterState::Jump;

	Super::Jump();

}

void ARPG_BaseCharacter::Skill_Melee()
{
	const FCharacterInfoTB* CharacterInfoTB = URpgGamePlayStatics::FindTable<FCharacterInfoTB>(CharacterInfoTableID);

	if (nullptr == CharacterInfoTB)
		return;

	UAnimMontage* AnimMontage = nullptr;
	const FSkillInfoTB* SkillInfoTB = nullptr;
	if (GetVelocity().Size2D() >= 300.0f || ECharacterState::Jump == CharacterState)
		SkillInfoTB = URpgGamePlayStatics::FindTable<FSkillInfoTB>(CharacterInfoTB->Skill_Melee_Move);
	else
		SkillInfoTB = URpgGamePlayStatics::FindTable<FSkillInfoTB>(CharacterInfoTB->Skill_Melee);

	if (nullptr == SkillInfoTB)
		return;

	if (!CheckAttackEnable(SkillInfoTB))
		return;

	AnimMontage = Cast<UAnimMontage>(URpgGamePlayStatics::LoadObjectFromPath(UAnimMontage::StaticClass(), SkillInfoTB->AnimMontage));
	
	if (IsValid(AnimMontage))
	{
		PlayAnimMontage(AnimMontage);
	}

	CurrentUsingSkill = SkillInfoTB;
}

void ARPG_BaseCharacter::Skill_Range()
{
	const FCharacterInfoTB* CharacterInfoTB = URpgGamePlayStatics::FindTable<FCharacterInfoTB>(CharacterInfoTableID);

	if (nullptr == CharacterInfoTB)
		return;

	const FSkillInfoTB* SkillInfoTB = URpgGamePlayStatics::FindTable<FSkillInfoTB>(CharacterInfoTB->Skill_Range);
	if (nullptr == SkillInfoTB)
		return;

	if (!CheckAttackEnable(SkillInfoTB))
		return;

	UAnimMontage* AnimMontage = Cast<UAnimMontage>(URpgGamePlayStatics::LoadObjectFromPath(UAnimMontage::StaticClass(), SkillInfoTB->AnimMontage));
	if (IsValid(AnimMontage))
	{
		PlayAnimMontage(AnimMontage);
	}

	CurrentUsingSkill = SkillInfoTB;
}

void ARPG_BaseCharacter::MoveFoward(float Val)
{
	if (!CheckMoveEnable())
		return;

	ARpg_BaseController* PC = Cast<ARpg_BaseController>(GetController());

	FVector MoveDirectionVector = GetActorForwardVector();
	if (IsValid(PC))
	{

//		if (!bWasJumping)
//		{
			ARpgCameraActor* RpgCameraActor = Cast<ARpgCameraActor>(PC->GetViewTargetCamera());
			if (IsValid(RpgCameraActor))
			{
				MoveDirectionVector = RpgCameraActor->GetCameraDirection();
				MoveDirectionVector.Z = 0.0f;
				MoveDirectionVector.Normalize();
			}

			UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement();
			CharacterMovementComp->AddInputVector(MoveDirectionVector*Val);
//		}
	}
}

void ARPG_BaseCharacter::MoveRight(float Val)
{
	if (!CheckMoveEnable())
		return;

	ARpg_BaseController* PC = Cast<ARpg_BaseController>(GetController());

	FVector MoveDirectionVector = GetActorForwardVector();
	if (IsValid(PC))
	{
//		if (!bWasJumping)
//		{
			ARpgCameraActor* RpgCameraActor = Cast<ARpgCameraActor>(PC->GetViewTargetCamera());
			if (IsValid(RpgCameraActor))
			{
				MoveDirectionVector = RpgCameraActor->GetCameraDirection();
				MoveDirectionVector.Z = 0.0f;
				MoveDirectionVector.Normalize();
				MoveDirectionVector = FVector::CrossProduct(FVector(0.0f, 0.0f, 1.0f), MoveDirectionVector);
			}

			UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement();
			CharacterMovementComp->AddInputVector(MoveDirectionVector*Val);
//		}
	}
}

void ARPG_BaseCharacter::CameraTurnYaw(float Val)
{
	AddControllerYawInput(Val);
}

void ARPG_BaseCharacter::CameraTurnPitch(float Val)
{
	AddControllerPitchInput(Val);
}

float ARPG_BaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHP == 0.0f)
		return 0.0f;

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP = FMath::Max<float>(0.0f, CurrentHP - DamageAmount);

	ARpg_BaseController* Rpg_BaseController = Cast<ARpg_BaseController>(GetController());
	ARPG_PlayGameState* RPG_PlayGameState = Cast<ARPG_PlayGameState>(URpgGamePlayStatics::GetGameState(GetWorld()));
	RPG_PlayGameState->DamageFromEnemy += (int)DamageAmount;

	if (CurrentHP == 0.0f)
	{
		if (RPG_PlayGameState)
		{
			RPG_PlayGameState->PlayerDead();
		}

		DisableInput(URpgGamePlayStatics::GetRpgBaseController(GetWorld(), 0));
		GetMesh()->SetSimulatePhysics(true);
	}

	
	if (Rpg_BaseController)
	{
		ARPG_HUD* RPG_HUD = Cast<ARPG_HUD>(Rpg_BaseController->GetHUD());
		if (RPG_HUD)
		{
			UIngameWindow* IngameWindow = Cast<UIngameWindow>(RPG_HUD->CurrentOpenedWindow);
			if (IngameWindow)
			{
				IngameWindow->SetCharacterHP(CurrentHP / CharacterInfoTB->HP);
			}
		}
	}

	return DamageAmount;
}

TSubclassOf<ACameraActor> ARPG_BaseCharacter::GetCharacterDefaultCameraClass()
{
	TSubclassOf<ACameraActor> RetClass;
	RetClass = ARpgCharacterCamera::StaticClass();
	
	return RetClass;
}

void ARPG_BaseCharacter::SetInputFlag(FInputFlag InputFlag)
{
	CharacterInputFlag = InputFlag;
}

bool ARPG_BaseCharacter::CheckMoveEnable()
{
	return (ECharacterState::Idle == CharacterState) && CharacterInputFlag.Move;
}

bool ARPG_BaseCharacter::CheckJumpEnable()
{
	return  (ECharacterState::Idle == CharacterState) && (true == CharacterInputFlag.Jump);
}

bool ARPG_BaseCharacter::CheckAttackEnable(const FSkillInfoTB* SkillInfoTB)
{
	bool RetVal = true;

	if (ECharacterState::Idle == CharacterState && false == SkillInfoTB->UseEnableIdle)
		return false;

	if (ECharacterState::Jump == CharacterState && false == SkillInfoTB->UseEnableJump)
		return false;

	return CharacterInputFlag.Attack;
}

void ARPG_BaseCharacter::OnAnimSequenceEnd(class UAnimSequenceBase* Animation)
{
	switch (CharacterState)
	{
	case ECharacterState::Jump:
		if (Animation->GetFName() == TEXT("Exo_Jump_Copy") || Animation->GetFName() == TEXT("Exo_Running_Jump_Copy"))
		{
			CharacterState = ECharacterState::Idle;
		}
		break;
	default:
		break;
	}
}

#if WITH_EDITOR
void ARPG_BaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
/*
	FName ChangedPropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.GetPropertyName() : "";

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(ARPG_BaseCharacter, CharacterInfoTableID))
	{
		LoadSkeletalMeshByTable(CharacterInfoTableID);
	}
*/
}
#endif