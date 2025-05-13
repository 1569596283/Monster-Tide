// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameGameMode.h"
#include "Data/LevelData.h"
#include "Data/RolePropertyData.h"
#include "Levels/LevelManager.h"
#include "Roles/EnemyManager.h"
#include "Roles/Enemys/EnemyBase.h"
#include <Kismet/KismetSystemLibrary.h>

void AGameGameMode::BeginPlay()
{
	LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	LevelManager->InitLevel();
	HP = LevelManager->CurLevelConfig->HP;
	auto EnemyMgr = GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>();
	EnemyMgr->EnemyArrived.AddUObject(this, &AGameGameMode::OnEnemyArrived);
	EnemyMgr->EnemyDead.AddUObject(this, &AGameGameMode::OnEnemyDead);
}

void AGameGameMode::OnEnemyArrived(TObjectPtr<AEnemyBase> Enemy)
{
	HP -= Enemy->GetDamage();
	if (HP <= 0) {
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	}
}

void AGameGameMode::OnEnemyDead(TObjectPtr<AEnemyBase> Enemy)
{
}
