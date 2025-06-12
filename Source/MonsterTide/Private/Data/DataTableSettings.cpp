// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataTableSettings.h"

UDataTable* UDataTableSettings::GetGameEnemyDataTable() const
{
	return GameEnemyDataTable.LoadSynchronous(); // 同步加载（适合小表格）
}

UDataTable* UDataTableSettings::GetEnemyPropertyDataTable() const
{
	return EnemyPropertyDataTable.LoadSynchronous(); // 同步加载（适合小表格）
}

UDataTable* UDataTableSettings::GetHeroPropertyDataTable() const
{
	return HeroPropertyDataTable.LoadSynchronous(); // 同步加载（适合小表格）
}

UDataTable* UDataTableSettings::GetLevelDataTable() const
{
	return LevelDataTable.LoadSynchronous(); // 同步加载（适合小表格）
}

UDataTable* UDataTableSettings::GetSkillDataTable() const
{
	return SkillDataTable.LoadSynchronous(); // 同步加载（适合小表格）
}
