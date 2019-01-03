// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_TableLoader.h"
#include "RpgGamePlayStatics.h"


UDataTable* URPG_TableLoader::GetDataTableAsset(FString AssetPath)
{
	UDataTable* DataTable = Cast<UDataTable>(URpgGamePlayStatics::LoadObjectFromPath(UDataTable::StaticClass(), AssetPath));

	return DataTable;
}