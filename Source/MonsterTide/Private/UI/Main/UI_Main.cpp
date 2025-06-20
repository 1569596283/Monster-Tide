// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_Main.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/SaveManager.h"
#include "Game/MainPlayerController.h"
#include "Levels/LevelManager.h"
#include "Roles/HeroManager.h"
#include <Kismet/GameplayStatics.h>

void UUI_Main::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Play != nullptr) {
		Btn_Play->OnClicked.AddDynamic(this, &UUI_Main::OnBtnPlayClicked);
	}
	if (Btn_Hero != nullptr) {
		Btn_Hero->OnClicked.AddDynamic(this, &UUI_Main::OnBtnHeroClicked);
	}
	if (Btn_Recruit != nullptr) {
		Btn_Recruit->OnClicked.AddDynamic(this, &UUI_Main::OnBtnRecruitClicked);
	}
	if (Btn_Return != nullptr) {
		Btn_Return->OnClicked.AddDynamic(this, &UUI_Main::OnBtnReturnClicked);
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

void UUI_Main::OnBtnRecruitClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC)) {
		MainPC->OpenRecruitUMG();
	}
}

void UUI_Main::OnBtnReturnClicked()
{
	UGameplayStatics::OpenLevel(this, FName(FString("StartMap")));
	GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->ClearHero();
}
