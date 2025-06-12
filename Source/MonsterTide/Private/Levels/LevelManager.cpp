// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/LevelManager.h"
#include "Data/LevelData.h"
#include "Data/GameEnemyData.h"
#include "Roles/EnemyManager.h"
#include <Kismet/GameplayStatics.h>

void ULevelManager::OpenLevel()
{
	FString LevelName = "GameMap_" + FString::FromInt(CurLevel);
	UGameplayStatics::OpenLevel(this, FName(LevelName));
}

void ULevelManager::OpenLevel(int Level)
{
	CurLevel = Level;
	OpenLevel();
}

void ULevelManager::OpenNextLevel()
{
	if (HasNextLevel()) {
		CurLevel++;
		OpenLevel();
	}
}

void ULevelManager::InitLevel()
{
	LevelTime = 0;
	FairyStone = 0;
	CurLevelConfig = GetLevelConfig(CurLevel);
	EnemyArr.Empty();
	int EnemyNum = 0;
	for (int i = CurLevelConfig->Enemy[0]; i <= CurLevelConfig->Enemy[1]; i++) {
		FGameEnemyConfig GameEnemyConfig = GetGameEnemyConfig(i);
		EnemyArr.Push(GameEnemyConfig);
		EnemyNum += GameEnemyConfig.Number;
	}

	GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>()->SetLevelEnemyNum(EnemyNum);
}

int ULevelManager::GetCueLevel()
{
	return CurLevel;
}

void ULevelManager::LevelStart()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULevelManager::Tick, 0.1f, true);
}

ELevelType ULevelManager::GetLevelType()
{
	return CurLevelType;
}

void ULevelManager::GameOver()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

int ULevelManager::GetBattleHeroNumber() const
{
	return CurLevelConfig->HerosNum;
}

int ULevelManager::GetEnemyNumber() const
{
	int Num = 0;
	for (FGameEnemyConfig cfg : EnemyArr) {
		Num += cfg.Number;
	}
	return Num;
}

int ULevelManager::GetFairyStone() const
{
	return FairyStone;
}

int ULevelManager::GetFairyStone(int HP)
{
	FairyStone = CurLevelConfig->FairyStone * (1.f * HP / CurLevelConfig->HP);
	return FairyStone;
}

bool ULevelManager::HasNextLevel()
{
	FString LevelName = "GameMap_" + FString::FromInt(CurLevel + 1);
	FString LevelPath = FString::Printf(TEXT("/Game/Maps/Classic/%s"), *LevelName);
	// 检查关卡是否存在
	return FPackageName::DoesPackageExist(LevelPath);
}

void ULevelManager::CreateEnemy()
{
	for (int i = EnemyArr.Num() - 1; i >= 0; i--) {
		if (FMath::IsNearlyEqual(EnemyArr[i].ArrivalTime, LevelTime, 0.05)) {
			GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>()->CreateEnemys(EnemyArr[i]);
			EnemyArr.RemoveAt(i);
		}
	}
}

void ULevelManager::Tick()
{
	LevelTime += 0.1;
	OnTimeAdd.Broadcast(LevelTime);
	if (!EnemyArr.IsEmpty()) {
		CreateEnemy();
	}
}