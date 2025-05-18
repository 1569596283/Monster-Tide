// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/LevelManager.h"
#include "Data/LevelData.h"
#include "Data/GameEnemyData.h"
#include "Roles/EnemyManager.h"
#include <Kismet/GameplayStatics.h>

void ULevelManager::OpenLevel()
{
	UGameplayStatics::OpenLevel(this, FName("GameMap_1"));
	CurLevel = 1;
}

void ULevelManager::OpenLevel(int Level)
{
	FString HPText = "GameMap_" + FString::FromInt(Level);
	UGameplayStatics::OpenLevel(this, FName(HPText));
	CurLevel = Level;
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