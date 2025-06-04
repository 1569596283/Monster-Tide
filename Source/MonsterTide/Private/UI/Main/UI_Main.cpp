// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_Main.h"
#include "Components/Button.h"
#include "Levels/LevelManager.h"
#include "Game/MainPlayerController.h"

void UUI_Main::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Play != nullptr) {
		Btn_Play->OnClicked.AddDynamic(this, &UUI_Main::OnBtnPlayClicked);
	}
	if (Btn_Hero != nullptr) {
		Btn_Hero->OnClicked.AddDynamic(this, &UUI_Main::OnBtnHeroClicked);
	}
}

void UUI_Main::OnBtnPlayClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC)) {
		MainPC->OpenLevelUMG();
	}
}

void UUI_Main::OnBtnHeroClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC)) {
		MainPC->OpenHeroUMG();
	}
}
