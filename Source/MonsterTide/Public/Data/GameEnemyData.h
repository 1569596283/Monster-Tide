// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEnemyData.generated.h"

enum class ERoleType : uint8;

/* 游戏中怪物属性配置 */
USTRUCT(BlueprintType)
struct FGameEnemyConfig :public FTableRowBase
{
	GENERATED_BODY()

	FGameEnemyConfig();
	FGameEnemyConfig(FGameEnemyConfig* Cfg);

	UPROPERTY(EditDefaultsOnly)
	ERoleType Type;

	UPROPERTY(EditDefaultsOnly)
	int EnemyLevel = 1;

	UPROPERTY(EditDefaultsOnly)
	int Path = 1;

	UPROPERTY(EditDefaultsOnly)
	float ArrivalTime = 10;

	UPROPERTY(EditDefaultsOnly)
	int Number = 10;

	UPROPERTY(EditDefaultsOnly)
	float Interval = 1.0f;
};

FGameEnemyConfig GetGameEnemyConfig(int id);

bool GameEnemyConfigEqual(FGameEnemyConfig* aCfg, FGameEnemyConfig* bCfg);