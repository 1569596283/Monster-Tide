// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GamePlayerController.h"
#include "UI/Game/UI_Game.h"
#include "UI/Settlement/UI_Settlement.h"
#include "Roles/EnemyManager.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGamePlayerController::OpenSettlementUI(bool Victory)
{
	if (UI_Game) {
		UI_Game->RemoveFromParent();
		UI_Game = nullptr;
	}

	if (UI_SettlementClass != nullptr) {
		UI_Settlement = CreateWidget<UUI_Settlement>(this, UI_SettlementClass);
		UI_Settlement->AddToViewport();
		UI_Settlement->InitResult(Victory);
	}
}

void AGamePlayerController::OpenGameUI()
{
	if (UI_GameClass != nullptr) {
		UI_Game = CreateWidget<UUI_Game>(this, UI_GameClass);
		UI_Game->AddToViewport();
		UI_Game->InitGameUI();
		auto EnemyMgr = GetWorld()->GetGameInstance()->GetSubsystem<UEnemyManager>();
		EnemyMgr->EnemyCreate.AddUObject(UI_Game, &UUI_Game::RefreshEnemyProperss);
	}
}
