// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelManager.generated.h"

enum class ELevelType :uint8;
struct FGameEnemyConfig;
struct FLevelConfig;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API ULevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void OpenLevel();
	void OpenLevel(int Level);
	void OpenNextLevel();

	void InitLevel();
	int GetCueLevel();

	ELevelType GetLevelType();
	void GameOver();

	FLevelConfig* CurLevelConfig;

	int GetEnemyNumber() const;

	bool HasNextLevel();
private:
	UPROPERTY()
	/* ��ǰ�ؿ�������ʱ�� */
	float LevelTime = 0;
	/* ��ǰ�ؿ����� */
	ELevelType CurLevelType;
	/* ��ǰ�ؿ� */
	int CurLevel = 1;

	FTimerHandle TimerHandle;
	TArray<FGameEnemyConfig> EnemyArr;

	void CreateEnemy();

	void Tick();
};
