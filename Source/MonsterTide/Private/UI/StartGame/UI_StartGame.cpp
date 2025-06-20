// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StartGame/UI_StartGame.h"
#include "Components/Button.h"
#include "Game/SaveManager.h"
#include "Roles/HeroManager.h"
#include "Levels/Levelmanager.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void UUI_StartGame::OnStartCilcked()
{
	GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->InitSaveData();
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->InitHeroProperty();
	UGameplayStatics::OpenLevel(this, FName("MainMap"));
}

void UUI_StartGame::OnContinueCilcked()
{
 	bool Success = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>()->ReadSaveData("TestSaveData");
	if (Success) {
		GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->InitHeroProperty();
		UGameplayStatics::OpenLevel(this, FName("MainMap"));
	}
}

void UUI_StartGame::OnExitCilcked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UUI_StartGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_Start != nullptr) {
		Btn_Start->OnClicked.AddDynamic(this, &UUI_StartGame::OnStartCilcked);
	}
	if (Btn_Continue != nullptr) {
		Btn_Continue->OnClicked.AddDynamic(this, &UUI_StartGame::OnContinueCilcked);
	}
	if (Btn_Exit != nullptr) {
		Btn_Exit->OnClicked.AddDynamic(this, &UUI_StartGame::OnExitCilcked);
	}
}
