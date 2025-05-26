// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameGameMode.h"
#include "Game/GamePlayerController.h"
#include "Game/SaveManager.h"
#include "Data/LevelData.h"
#include "Data/RolePropertyData.h"
#include "Levels/LevelManager.h"
#include "Roles/HeroManager.h"
#include "Roles/EnemyManager.h"
#include "Roles/Enemys/EnemyBase.h"
#include "Skills/SkillManager.h"
#include <Kismet/KismetSystemLibrary.h>

void AGameGameMode::BeginPlay()
{
	LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	LevelManager->InitLevel();
	HP = LevelManager->CurLevelConfig->HP;
	auto EnemyMgr = GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>();
	EnemyMgr->EnemyArrived.AddUObject(this, &AGameGameMode::OnEnemyArrived);
	EnemyMgr->EnemyDead.AddUObject(this, &AGameGameMode::OnEnemyDead);
	GetWorld()->GetGameInstance()->GetSubsystem<USkillManager>()->InitSkill();
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->EnterBattle();
}

void AGameGameMode::OnEnemyArrived(TObjectPtr<AEnemyBase> Enemy)
{
	HP -= Enemy->GetDamage();
	if (HP <= 0) {
		Defeat();
	}
	else {
		CheckVictory();
	}
}

void AGameGameMode::OnEnemyDead(TObjectPtr<AEnemyBase> Enemy)
{
	float Exp = Enemy->GetRoleProperty()->Exp;
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->AddExp(Enemy->Killer, Exp);
	CheckVictory();
}

void AGameGameMode::CheckVictory()
{
	int Num1 = LevelManager->GetEnemyNumber();
	int Num2 = GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>()->GetEnemyNumber();
	if (Num1 + Num2 == 0) {
		auto SaveMgr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>();
		SaveMgr->SetCurLevel(LevelManager->GetCueLevel());
		TArray<FRoleProperty> RolePropertyArr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetHeroBasePropertyArray();
		SaveMgr->SetHeroProperty(&RolePropertyArr);
		GameOver(true);
		SaveMgr->SaveGameData("TestSaveData");
	}
}

void AGameGameMode::Defeat()
{
	GameOver(false);
}

void AGameGameMode::GameOver(bool Victory)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (AGamePlayerController* GPC = Cast<AGamePlayerController>(PC)) {
		GPC->OpenSettlementUI(false);
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->ExitBattle();
}
