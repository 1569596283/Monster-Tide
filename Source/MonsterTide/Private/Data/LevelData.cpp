// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LevelData.h"

FLevelConfig* GetLevelConfig(int Level)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_Level.DT_Level'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(FString::FromInt(Level));
		FLevelConfig* LevelConfig = DataTable->FindRow<FLevelConfig>(RowName, ContextString);
		if (LevelConfig)
			return LevelConfig;
	}
	return nullptr;
}
