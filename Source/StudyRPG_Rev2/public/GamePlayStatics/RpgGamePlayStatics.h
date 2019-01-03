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
	/** 입력받은 PathName에 해당 하는 클래스 정보를 출력하는 함수
	* @ PathName : 클래스 정보를 받고자하는 에셋 경로. 경로의 경우 레퍼런스에서 뒤의 .xxxx를 뺀 나머지 경로를 입력한다.
	* (ex 에셋레퍼런스 가 [에셋폴더경로]/XXXX.XXXX 인경우 [에셋폴더경로]/XXXX 까지만 입력
	*/
	static UClass* LoadClassFromPath(UClass* BaseClass, FString PathName);

	/** 입력받은 PathName에 해당 하는 오브젝트 정보를 출력하는 함수
	* @ PathName : 클래스 정보를 받고자하는 에셋 경로. 경로의 경우 레퍼런스에서 뒤의 .xxxx를 뺀 나머지 경로를 입력한다.
	* (ex 에셋레퍼런스 가 [에셋폴더경로]/XXXX.XXXX 인경우 [에셋폴더경로]/XXXX 까지만 입력
	*/
	static UObject* LoadObjectFromPath(UClass* BaseClass, FString PathName);
	
	/** 입력받은 TableType 형식의 테이블을 검색. 반환하는 함수
	* TableType 테이블 정의에는 반드시 static FString GetTableAssetPath() 함수로 해당 TableType이 참조하는 에셋경로를 반환해야한다.
	* @ RowID : 찾고자 하는 TableType의 키값
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
