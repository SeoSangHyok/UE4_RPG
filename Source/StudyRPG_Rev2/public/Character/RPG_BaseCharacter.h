// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Table/Rpg_TableDef.h"
#include "RPG_BaseCharacter.generated.h"

USTRUCT(BlueprintType)
struct FInputFlag
{
	GENERATED_USTRUCT_BODY()

	FInputFlag()
	{
		Move = true;
		Jump = true;
		Attack = true;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InputFlag")
	bool Move;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InputFlag")
	bool Jump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InputFlag")
	bool Attack;
};

UENUM (BlueprintType)
enum class ECharacterState : uint8
{
	Idle,
	Jump
};

UCLASS()
class STUDYRPG_REV2_API ARPG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPG_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform);

	UFUNCTION(BlueprintCallable, Category = "RPG_BaseCharacter")
	bool LoadSkeletalMeshByTable(int32 TableID);

	virtual void Jump();
	virtual void Skill_Melee();
	virtual void Skill_Range();

	virtual void MoveFoward(float Val);
	virtual void MoveRight(float Val);
	virtual void CameraTurnYaw(float Val);
	virtual void CameraTurnPitch(float Val);	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "RPG_BaseCharacter")
	virtual TSubclassOf<ACameraActor> GetCharacterDefaultCameraClass();

	void SetInputFlag(FInputFlag InputFlag);

	bool CheckMoveEnable();
	bool CheckJumpEnable();
	bool CheckAttackEnable(const FSkillInfoTB* SkillInfoTB);

	ECharacterState GetCharacterState() { return CharacterState; }

	void OnAnimSequenceEnd(class UAnimSequenceBase* Animation);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	const FSkillInfoTB* CurrentUsingSkill = nullptr;
	const FCharacterInfoTB* CharacterInfoTB = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG_BaseCharacter")
	float CurrentHP = 0.0f;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseCharacter", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseCharacter", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseCharacter", meta = (AllowPrivateAccess = "true"))
	int CharacterInfoTableID = 1000;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseCharacter", meta = (AllowPrivateAccess = "true"))
	FInputFlag CharacterInputFlag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseCharacter", meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseCharacter", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponComp;
};
