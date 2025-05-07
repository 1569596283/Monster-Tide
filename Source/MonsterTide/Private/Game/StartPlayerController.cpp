// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/StartPlayerController.h"
#include "UI/StartGame/UI_StartGame.h"

void AStartPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UI_StartGameClass != nullptr) {
		UI_StartGame = CreateWidget<UUI_StartGame>(this, UI_StartGameClass);
		UI_StartGame->AddToViewport();
	}
}
