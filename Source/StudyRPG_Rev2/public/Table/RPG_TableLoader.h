// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "RPG_TableLoader.generated.h"

/**
 * 
 */
UCLASS()
class STUDYRPG_REV2_API URPG_TableLoader : public UObject
{
	GENERATED_BODY()
	
public:
	template <typename TableType>
	TableType* FindTable(FString AssetPath, int RowID)
	{
		TableType* RetTable = nullptr;

		const FString ContextString = FString::Printf(TEXT("URPG_TableLoader::FindTable(FString AssetPath[%s] int RowID[%d])"), *AssetPath, RowID);
		UDataTable* DataTable = GetDataTableAsset(AssetPath);
		if (IsValid(DataTable))
		{
			RetTable = DataTable->FindRow<TableType>(*FString::Printf(TEXT("%d"), RowID), ContextString);
		}

		return RetTable;
	}

	template <typename TableType>
	TableType* FindTable(int RowID)
	{
		return FindTable<TableType>(TableType::GetTableAssetPath(), RowID);
	}

	template <typename TableType>
	void GetTableElemList(OUT TArray<TableType*>& ElemList)
	{
		int RetVal = 0;

		const FString ContextString = FString::Printf(TEXT("URPG_TableLoader::GetTableElemList(FString AssetPath[%s])"), *TableType::GetTableAssetPath());
		UDataTable* DataTable = GetDataTableAsset(TableType::GetTableAssetPath());
		if (IsValid(DataTable))
		{
			DataTable->GetAllRows<TableType>(ContextString, ElemList);
		}
	}

private:
	// TableLoader 클래스는 RpgGamePlaystatics에서 사용할것이라 RpgGamePlaystatics 함수를 사용하는 부분을 따로 빼서 cpp에 구현(상호참조 예방차원)
	UDataTable* GetDataTableAsset(FString AssetPath);
};
