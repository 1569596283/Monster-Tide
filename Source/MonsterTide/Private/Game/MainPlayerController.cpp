// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainPlayerController.h"
#include "UI/Main/UI_Main.h"
#include "UI/Main/UI_SelectLevel.h"
#include "UI/Main/UI_Hero.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ShowMainUMG();
}

void AMainPlayerController::ShowMainUMG()
{
	if (UI_Main) {
		UI_Main->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		if (UI_MainClass != nullptr) {
			UI_Main = CreateWidget<UUI_Main>(this, UI_MainClass);
			UI_Main->AddToViewport();
		}
	}
	UI_Main->RefreshInfo();
}

void AMainPlayerController::OpenLevelUMG()
{
	if (UI_SelectLevelClass != nullptr) {
		UI_Main->SetVisibility(ESlateVisibility::Collapsed);
		UI_SelectLevel = CreateWidget<UUI_SelectLevel>(this, UI_SelectLevelClass);
		UI_SelectLevel->AddToViewport();
	}
}

void AMainPlayerController::CloseLevelUMG()
{
	UI_SelectLevel->RemoveFromParent();
	ShowMainUMG();
	UI_SelectLevel = nullptr;
}

void AMainPlayerController::OpenHeroUMG()
{
	if (UI_HeroClass != nullptr) {
		UI_Main->SetVisibility(ESlateVisibility::Collapsed);
		UI_Hero = CreateWidget<UUI_Hero>(this, UI_HeroClass);
		UI_Hero->AddToViewport();
	}
}

void AMainPlayerController::CloseHeroUMG()
{
	UI_Hero->RemoveFromParent();
	ShowMainUMG();
	UI_Hero = nullptr;
}
