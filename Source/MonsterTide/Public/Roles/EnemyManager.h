// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemyManager.generated.h"

struct FGameEnemyConfig;

struct FCreateStruct
{
	FCreateStruct(FGameEnemyConfig* Cfg);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	FGameEnemyConfig* GameEnemyConfig;
};

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API UEnemyManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	void CreateEnemys(FGameEnemyConfig EnemyConfig);

private:
	TArray<FCreateStruct*> CreateArray;

	UFUNCTION()
	void CreateEnemy(FGameEnemyConfig EnemyConfig);

};
