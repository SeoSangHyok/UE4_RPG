// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Table/RPG_TableLoader.h"
#include "Controller/Rpg_BaseController.h"
#include "RpgGamePlayStatics.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URpgGamePlayStatics : public UGameplayStatics
{
	GENERATED_BODY()


public:
	/** �Է¹��� PathName�� �ش� �ϴ� Ŭ���� ������ ����ϴ� �Լ�
	* @ PathName : Ŭ���� ������ �ް����ϴ� ���� ���. ����� ��� ���۷������� ���� .xxxx�� �� ������ ��θ� �Է��Ѵ�.
	* (ex ���·��۷��� �� [�����������]/XXXX.XXXX �ΰ�� [�����������]/XXXX ������ �Է�
	*/
	static UClass* LoadClassFromPath(UClass* BaseClass, FString PathName);

	/** �Է¹��� PathName�� �ش� �ϴ� ������Ʈ ������ ����ϴ� �Լ�
	* @ PathName : Ŭ���� ������ �ް����ϴ� ���� ���. ����� ��� ���۷������� ���� .xxxx�� �� ������ ��θ� �Է��Ѵ�.
	* (ex ���·��۷��� �� [�����������]/XXXX.XXXX �ΰ�� [�����������]/XXXX ������ �Է�
	*/
	static UObject* LoadObjectFromPath(UClass* BaseClass, FString PathName);
	
	/** �Է¹��� TableType ������ ���̺��� �˻�. ��ȯ�ϴ� �Լ�
	* TableType ���̺� ���ǿ��� �ݵ�� static FString GetTableAssetPath() �Լ��� �ش� TableType�� �����ϴ� ���°�θ� ��ȯ�ؾ��Ѵ�.
	* @ RowID : ã���� �ϴ� TableType�� Ű��
	*/
	template <typename TableType>
	static const TableType* FindTable(int RowID)
	{
		URPG_TableLoader* RpgTableLoader = GetRpgTableLoader();
		return RpgTableLoader->FindTable<TableType>(RowID);
	}

	template <typename TableType>
	static void GetTableElemList(OUT TArray<TableType*>& ElemList)
	{
		URPG_TableLoader* RpgTableLoader = GetRpgTableLoader();
		return RpgTableLoader->GetTableElemList<TableType>(ElemList);
	}

	UFUNCTION(BlueprintPure, Category = "URpgGamePlayStatics", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static ARpg_BaseController* GetRpgBaseController(const UObject* WorldContextObject, int32 PlayerIndex);

	UFUNCTION()
	static URPG_TableLoader* GetRpgTableLoader();

	UFUNCTION()
	static void LoadLevelUsingLevelTable(const UObject* WorldContext, int32 LevelID);

public:
};
