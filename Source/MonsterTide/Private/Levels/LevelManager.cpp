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
	//CurLevel++;
	OpenLevel();
}

void ULevelManager::InitLevel()
{
	LevelTime = 0;
	CurLevelConfig = GetLevelConfig(CurLevel);
	EnemyArr.Empty();
	for (int i = CurLevelConfig->Enemy[0]; i <= CurLevelConfig->Enemy[1]; i++) {
		FGameEnemyConfig GameEnemyConfig = GetGameEnemyConfig(i);
		EnemyArr.Push(GameEnemyConfig);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ULevelManager::Tick, 0.1f, true);
}

int ULevelManager::GetCueLevel()
{
	return CurLevel;
}

void ULevelManager::GameOver()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

int ULevelManager::GetEnemyNumber() const
{
	int Num = 0;
	for (FGameEnemyConfig cfg : EnemyArr) {
		Num += cfg.Number;
	}
	return Num;
}

void ULevelManager::CreateEnemy()
{
	for (int i = EnemyArr.Num() - 1; i >= 0; i--) {
		if (FMath::IsNearlyEqual(EnemyArr[i].ArrivalTime, LevelTime, 0.05)) {
			GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>()->CreateEnemys(EnemyArr[i]);
			EnemyArr.RemoveAt(i);
		}
	}

	if (EnemyArr.IsEmpty()) {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

}

void ULevelManager::Tick()
{
	LevelTime += 0.1;
	CreateEnemy();
}