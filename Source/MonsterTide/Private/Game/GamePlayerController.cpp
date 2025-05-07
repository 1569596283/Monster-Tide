// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GamePlayerController.h"
#include "UI/Game/UI_Game.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UI_GameClass != nullptr) {
		UI_Game = CreateWidget<UUI_Game>(this, UI_GameClass);
		UI_Game->AddToViewport();
	}
}
