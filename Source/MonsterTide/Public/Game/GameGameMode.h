// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameGameMode.generated.h"

class ULevelManager;
class AEnemyBase;

/**
 * 
 */
UCLASS()
class MONSTERTIDE_API AGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	int HP;

private :
	UPROPERTY()
	TObjectPtr<ULevelManager> LevelManager;

	void OnEnemyArrived(TObjectPtr<AEnemyBase> Enemy);
	void OnEnemyDead(TObjectPtr<AEnemyBase> Enemy);

	void CheckVictory();
	void Defeat();
};
