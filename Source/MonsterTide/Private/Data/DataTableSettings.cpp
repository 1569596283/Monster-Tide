// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataTableSettings.h"

UDataTable* UDataTableSettings::GetGameEnemyDataTable() const
{
	return GameEnemyDataTable.LoadSynchronous(); // ͬ�����أ��ʺ�С���
}

UDataTable* UDataTableSettings::GetEnemyPropertyDataTable() const
{
	return EnemyPropertyDataTable.LoadSynchronous(); // ͬ�����أ��ʺ�С���
}

UDataTable* UDataTableSettings::GetHeroPropertyDataTable() const
{
	return HeroPropertyDataTable.LoadSynchronous(); // ͬ�����أ��ʺ�С���
}

UDataTable* UDataTableSettings::GetLevelDataTable() const
{
	return LevelDataTable.LoadSynchronous(); // ͬ�����أ��ʺ�С���
}

UDataTable* UDataTableSettings::GetSkillDataTable() const
{
	return SkillDataTable.LoadSynchronous(); // ͬ�����أ��ʺ�С���
}
