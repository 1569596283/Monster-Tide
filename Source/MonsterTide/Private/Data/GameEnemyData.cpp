// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GameEnemyData.h"
#include "Data/RolePropertyData.h"

FGameEnemyConfig GetGameEnemyConfig(int id)
{
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_GameEnemy.DT_GameEnemy'")));
	if (DataTable) {
		FString ContextString = "Context";
		FName RowName = FName(FString::FromInt(id));
		FGameEnemyConfig* GameEnemyConfig = DataTable->FindRow<FGameEnemyConfig>(RowName, ContextString);
		if (GameEnemyConfig)
			return *GameEnemyConfig;
	}
	return FGameEnemyConfig();
}

bool GameEnemyConfigEqual(FGameEnemyConfig* aCfg, FGameEnemyConfig* bCfg)
{
	if (aCfg->Type != bCfg->Type) {
		return false;
	}
	if (aCfg->Path != bCfg->Path) {
		return false;
	}
	if (aCfg->ArrivalTime != bCfg->ArrivalTime) {
		return false;
	}
	return true;
}

FGameEnemyConfig::FGameEnemyConfig()
{
	Type = ERoleType::Role;
}

FGameEnemyConfig::FGameEnemyConfig(FGameEnemyConfig* Cfg)
{
	Type = Cfg->Type;
	EnemyLevel = Cfg->EnemyLevel;
	Path = Cfg->Path;
	ArrivalTime = Cfg->ArrivalTime;
	Number = Cfg->Number;
	Interval = Cfg->Interval;
}
