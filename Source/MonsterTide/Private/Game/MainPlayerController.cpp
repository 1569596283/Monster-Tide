// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainPlayerController.h"
#include "UI/Main/UI_Main.h"
#include "UI/Main/UI_SelectLevel.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UI_MainClass != nullptr) {
		UI_Main = CreateWidget<UUI_Main>(this, UI_MainClass);
		UI_Main->AddToViewport();
	}
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
	UI_Main->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UI_SelectLevel = nullptr;
}
