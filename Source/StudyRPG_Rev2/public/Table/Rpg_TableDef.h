// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"	// For use FTableRowBase
#include "UI/WindowBase.h"
#include "Rpg_TableDef.generated.h"

/**
 *  언리얼 해더툴에 구조체가 처리되도록 하기위한 더미 오브젝트 클래스
 */
UCLASS()
class STUDYRPG_REV2_API URpg_TableDef : public UObject
{
	GENERATED_BODY()
};


USTRUCT(BlueprintType)
struct FCharacterInfoTB : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	static FString GetTableAssetPath()
	{
		return TEXT("/Game/Table/Character");
	}

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	int32 ID;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	FString SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	FString AnimationBP;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	float DefaultRotateYaw;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	float CapsuleHalfHeight;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	float CapsuleRadius;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	int32 Skill_Melee;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	int32 Skill_Range;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	int32 Skill_Melee_Move;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	int32 Weapon;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	float HP;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	FString Thumbnail;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterInfoTB")
	FString CharacterName;
};

USTRUCT(BlueprintType)
struct FSkillInfoTB : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	static FString GetTableAssetPath()
	{
		return TEXT("/Game/Table/Skill");
	}

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	int32 ID;

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	FString AnimMontage;

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	FString StartSectionName;

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	bool UseEnableIdle;

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	bool UseEnableJump;

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	float CoolTime;

	UPROPERTY(BlueprintReadOnly, Category = "SkillInfoTB")
	float Damage;
};

USTRUCT(BlueprintType)
struct FMonsterInfoTB : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	static FString GetTableAssetPath()
	{
		return TEXT("/Game/Table/Monster");
	}

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	int32 ID;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	FString SkeletalMesh;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float DefaultRotateYaw;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float CapsuleHalfHeight;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float CapsuleRadius;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	FString AnimationBP;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	FString BehaviourTree;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	int32 Skill1;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	int32 Skill2;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	int32 Skill3;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	int32 Weapon;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	int32 Armor;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float HP;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Speed;
};

USTRUCT(BlueprintType)
struct FEquipInfoTB : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	static FString GetTableAssetPath()
	{
		return TEXT("/Game/Table/Equip");
	}

	UPROPERTY(BlueprintReadOnly, Category = "EquipInfoTB")
	int32 ID;

	UPROPERTY(BlueprintReadOnly, Category = "EquipInfoTB")
	FString MeshType;

	UPROPERTY(BlueprintReadOnly, Category = "EquipInfoTB")
	FString Mesh;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	FString AttatchedSocket;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Loc_X;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Loc_Y;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Loc_Z;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Rot_X;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Rot_Y;

	UPROPERTY(BlueprintReadOnly, Category = "MonsterInfoTB")
	float Rot_Z;
};

USTRUCT(BlueprintType)
struct FWindowInfoTB : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	static FString GetTableAssetPath()
	{
		return TEXT("/Game/Table/Window");
	}

	UPROPERTY(BlueprintReadOnly, Category = "WindowInfoTB")
	int32 ID;

	UPROPERTY(BlueprintReadOnly, Category = "WindowInfoTB")
	ERpgWindowType WindowType;

	UPROPERTY(BlueprintReadOnly, Category = "WindowInfoTB")
	FString WidgetRefPath;

	UPROPERTY(BlueprintReadOnly, Category = "WindowInfoTB")
	bool NeedUIMode;

	UPROPERTY(BlueprintReadOnly, Category = "WindowInfoTB")
	bool IsWindow;
};

USTRUCT(BlueprintType)
struct FMapInfoTB : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	static FString GetTableAssetPath()
	{
		return TEXT("/Game/Table/Map");
	}

	UPROPERTY(BlueprintReadOnly, Category = "MapInfoTB")
	int32 ID;

	UPROPERTY(BlueprintReadOnly, Category = "MapInfoTB")
	FString MapPath;

	UPROPERTY(BlueprintReadOnly, Category = "MapInfoTB")
	FString MapName;

	UPROPERTY(BlueprintReadOnly, Category = "MapInfoTB")
	FString Thumbnail;

	UPROPERTY(BlueprintReadOnly, Category = "MapInfoTB")
	FString LoadingImage;

	UPROPERTY(BlueprintReadOnly, Category = "MapInfoTB")
	int32 TargetMonster;
};