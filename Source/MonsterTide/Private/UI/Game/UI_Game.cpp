// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UI_Game.h"
#include "UI/Game/UI_HeroItem.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Roles/HeroManager.h"
#include "Roles/RoleAttribute.h"

void UUI_Game::NativeOnInitialized()
{
	RefreshHeros();
}

void UUI_Game::RefreshHeros()
{
	TArray<TObjectPtr<URoleAttribute>> RAArr = GetWorld()->GetGameInstance()->GetSubsystem<UHeroManager>()->GetBattleHeroAttributeArray();
	for (int i = 0; i < RAArr.Num(); i++) {
		AddHeroItem(RAArr[i]);
	}
}

void UUI_Game::InitGameUI(FString LevelName)
{
	TB_Name->SetText(FText::FromString(LevelName));
}

void UUI_Game::RefreshEnemyProperss(float Percent)
{
	PB_Enemy->SetPercent(Percent);
}

void UUI_Game::AddHeroItem(TObjectPtr<URoleAttribute> RA)
{
	if (ScrHero && HeroItemClass) {
		UUI_HeroItem* item = CreateWidget<UUI_HeroItem>(this, HeroItemClass);
		ScrHero->AddChild(item);
		item->InitRoleAttribute(RA);
	}
}
