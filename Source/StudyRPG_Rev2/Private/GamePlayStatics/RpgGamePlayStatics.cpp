// Fill out your copyright notice in the Description page of Project Settings.

#include "RpgGamePlayStatics.h"
#include "Engine/World.h"
#include "Table/Rpg_TableDef.h"
#include "Engine/Engine.h"
#include "UI/RpgLoadingScreen.h"
#include "GameMode/RPGGameInstance.h"




UClass* URpgGamePlayStatics::LoadClassFromPath(UClass* BaseClass, FString PathName)
{
	if (nullptr == BaseClass || PathName.IsEmpty())
		return nullptr;

	/** 에셋 클래스는 에셋 레퍼런스 경로뒤에 _C 가 붙는 형식([레퍼런스경로]/XXXX.XXXX_C 형식)
	*  읽어들인 Path에서 .XXXX_C가 없는경후 해당 경로를 붙여준다.
	*/
	int PackageDelimPos = INDEX_NONE;
	PathName.FindChar(TCHAR('.'), PackageDelimPos);
	if (INDEX_NONE == PackageDelimPos)
	{
		int32 ObjectNameStart = INDEX_NONE;
		PathName.FindLastChar(TCHAR('/'), ObjectNameStart);
		if (ObjectNameStart != INDEX_NONE)
		{
			const FString ObjectName = PathName.Mid(ObjectNameStart + 1);
			PathName += TCHAR('.');
			PathName += ObjectName;
			PathName += TCHAR('_');
			PathName += TCHAR('C');
		}
	}

	return StaticLoadClass(BaseClass, nullptr, *PathName, nullptr, LOAD_None);
}

UObject* URpgGamePlayStatics::LoadObjectFromPath(UClass* BaseClass, FString PathName)
{
	if (BaseClass == nullptr || PathName.IsEmpty())
		return NULL;

	int32 PackageDelimPos = INDEX_NONE;
	PathName.FindChar(TCHAR('.'), PackageDelimPos);
	if (PackageDelimPos == INDEX_NONE)
	{
		int32 ObjectNameStart = INDEX_NONE;
		PathName.FindLastChar(TCHAR('/'), ObjectNameStart);
		if (ObjectNameStart != INDEX_NONE)
		{
			const FString ObjectName = PathName.Mid(ObjectNameStart + 1);
			PathName += TCHAR('.');
			PathName += ObjectName;
		}
	}

	return StaticLoadObject(BaseClass, nullptr, *PathName, nullptr);
}

ARpg_BaseController* URpgGamePlayStatics::GetRpgBaseController(const UObject* WorldContextObject, int32 PlayerIndex)
{
	return Cast<ARpg_BaseController>(GetPlayerController(WorldContextObject, PlayerIndex));
}

URPG_TableLoader* URpgGamePlayStatics::GetRpgTableLoader()
{
	static URPG_TableLoader* RetVal;
	if (nullptr == RetVal)
	{
		RetVal = NewObject<URPG_TableLoader>();
	}

	return RetVal;
}

void URpgGamePlayStatics::LoadLevelUsingLevelTable(const UObject* WorldContext, int32 LevelID)
{
	if (WorldContext == nullptr)
		return;

	const FMapInfoTB* MapInfoTB = URpgGamePlayStatics::FindTable<FMapInfoTB>(LevelID);
	if (MapInfoTB == nullptr)
		return;

	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance(WorldContext));
	URpgLoadingScreen* RpgLoadingScreen = RPGGameInstance->GetLoadingWidget();
	RpgLoadingScreen->SetLoadingImage(MapInfoTB->LoadingImage);

	OpenLevel(WorldContext, *MapInfoTB->MapPath);
}