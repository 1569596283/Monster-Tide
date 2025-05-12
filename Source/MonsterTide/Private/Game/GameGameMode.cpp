// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameGameMode.h"
#include "Levels/LevelManager.h"

void AGameGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AGameGameMode::BeginPlay"));
	LevelManager = GetWorld()->GetGameInstance()->GetSubsystem<ULevelManager>();
	LevelManager->InitLevel();
}
