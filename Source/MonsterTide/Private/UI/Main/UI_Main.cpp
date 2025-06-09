// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_Main.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/SaveManager.h"
#include "Game/MainPlayerController.h"
#include "Levels/LevelManager.h"

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

void UUI_Main::RefreshInfo()
{
	auto SaveMgr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>();
	TB_FairyStone->SetText(FText::FromString(FString::FromInt(SaveMgr->GetFairyStone())));
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
