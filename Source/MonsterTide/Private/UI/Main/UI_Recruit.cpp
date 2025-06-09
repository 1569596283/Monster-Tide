// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Main/UI_Recruit.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/SaveManager.h"
#include "Game/MainPlayerController.h"
#include "Roles/HeroManager.h"
#include "Data/HeroInfoData.h"


void UUI_Recruit::NativeOnInitialized()
{
	if (Btn_Return) {
		Btn_Return->OnClicked.AddDynamic(this, &UUI_Recruit::OnBtnReturnClicked);
	}
	if (Btn_Recruit) {
		Btn_Recruit->OnClicked.AddDynamic(this, &UUI_Recruit::OnBtnRecruitClicked);
	}

	RefreshInfo();
}

void UUI_Recruit::RefreshInfo()
{
	auto SaveMgr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>();
	TB_FairyStone->SetText(FText::FromString(FString::FromInt(SaveMgr->GetFairyStone())));
	TB_RecruitFS->SetText(FText::FromString(FString::FromInt(RecruitCost)));
}

void UUI_Recruit::OnBtnReturnClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;
	if (AMainPlayerController* MainPC = Cast<AMainPlayerController>(PC)) {
		MainPC->CloseRecruitUMG();
	}
}

void UUI_Recruit::OnBtnRecruitClicked()
{
	auto SaveMgr = GetWorld()->GetGameInstance()->GetSubsystem<USaveManager>();
	if (SaveMgr->ChangeFairyStone(-RecruitCost)) {
		FHeroInfo HeroInfo = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->AddRandomHero();
		SaveMgr->SaveGameData();
		RefreshInfo();
	}
}
