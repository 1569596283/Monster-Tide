// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LevelData.h"
#include "Data/DataTableSettings.h"

FLevelConfig GetLevelConfig(int Level)
{
	UDataTable* DataTable = GetMutableDefault<UDataTableSettings>()->GetLevelDataTable();
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(FString::FromInt(Level));
		FLevelConfig* LevelConfig = DataTable->FindRow<FLevelConfig>(RowName, ContextString);
		if (LevelConfig)
			return *LevelConfig;
	}
	return FLevelConfig();
}

TArray<FLevelConfig*> GetLevelConfigs(ELevelType Type)
{
	TArray<FLevelConfig*> Arr = TArray<FLevelConfig*>();
	UDataTable* DataTable = GetMutableDefault<UDataTableSettings>()->GetLevelDataTable();
	if (DataTable) {
	TArray<FName> RowNames = DataTable->GetRowNames();
		FString ContextString = "Context";
		// 遍历所有行
		for (const FName& RowName : RowNames)
		{
			FLevelConfig* LevelConfig = DataTable->FindRow<FLevelConfig>(RowName, "");
			if (LevelConfig && LevelConfig->Type == Type)
			{
				Arr.Push(LevelConfig);
			}
		}
	}
	return Arr;
}
