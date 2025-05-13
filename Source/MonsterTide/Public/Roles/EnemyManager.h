// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemyManager.generated.h"

struct FGameEnemyConfig;
class AEnemyBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyArrived, TObjectPtr<AEnemyBase>);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, TObjectPtr<AEnemyBase>);

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

	FOnEnemyArrived EnemyArrived;
	FOnEnemyDead EnemyDead;

private:
	TArray<FCreateStruct*> CreateArray;

	UPROPERTY()
	TArray <TObjectPtr< AEnemyBase >> EnemyArray;

	UFUNCTION()
	void CreateEnemy(FGameEnemyConfig EnemyConfig);

	void RemoveEnemy(TObjectPtr< AEnemyBase > Enemy);
	void OnEnemyDead(TObjectPtr< AEnemyBase > Enemy);
	void OnEnemyArrived(TObjectPtr< AEnemyBase > Enemy);
};
